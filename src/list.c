#include <stdlib.h>
#include <string.h>
#include "xfunctions.h"
#include "list.h"

static void
_list_f_no_delete(void *data)
{
  (void)data;
  return ;
}

static int
_list_f_compare(void *data_a, void *data_b)
{
  return (data_a == data_b ? 0 :
	  data_a < data_b ? -1 : 1);
}

void
list_init(t_list *list)
{
  memset(list, 0, sizeof(t_list));
  list->f_delete = &_list_f_no_delete;
  list->f_compare = &_list_f_compare;
}

void
list_full_init(t_list *list, void (*f_delete)(void *), int (*f_compare)(void *, void *))
{
  memset(list, 0, sizeof(t_list));
  list->f_delete = f_delete;
  list->f_compare = f_compare;
}

void
list_set_f_no_delete(t_list *list)
{
  list->f_delete = &_list_f_no_delete;
}

void
list_set_f_delete(t_list *list, void (*f_delete)(void *))
{
  list->f_delete = f_delete;
}

void
list_reset_f_compare(t_list *list)
{
  list->f_delete = &_list_f_no_delete;
}

void
list_set_f_compare(t_list *list, int (*f_compare)(void *, void *))
{
  list->f_compare = f_compare;
}

void
list_assign(t_list *list, t_lnode *head, t_lnode *tail)
{
  t_lnode *w;
  
  list->head = head;
  list->tail = tail;
  list->size = 0;
  w = head;
  while (head)
    {
      list->size += 1;
      w = w->next;
    }
}

void
list_push_front(t_list *list, void *data)
{
  t_lnode *node;

  node = xmalloc(sizeof(t_lnode));
  node->data = data;
  node->prev = NULL;
  if (list->size == 0)
    {
      node->next = NULL;
      list->head = node;
      list->tail = node;
    }
  else
    {	
      node->next = list->head;
      list->head->prev = node;
      list->head = node;
    }
  list->size++;
}

void
list_pop_front(t_list *list)
{
  t_lnode *node;
  
  if (list->size == 0)
    return ;
  node = list->head;
  list->head = node->next;
  list->head->prev = NULL;
  list->size--;
  if (list->f_delete)
    list->f_delete(node->data);
  free(node);
}

void
list_push_back(t_list *list, void *data)
{
  t_lnode *node;

  if (list->size == 0)
    {
      list_push_front(list, data);
      return ;
    }
  node = xmalloc(sizeof(t_lnode));
  node->data = data;
  node->prev = list->tail;
  node->next = NULL;
  list->tail->next = node;
  list->tail = node;
  list->size++;
}

void
list_pop_back(t_list *list)
{
  t_lnode *node;
  
  if (list->size == 0)
    return ;
  node = list->tail;
  list->tail = node->prev;
  list->tail->next = NULL;
  list->size--;
  if (list->f_delete)
    list->f_delete(node->data);
  free(node);
}

void
list_insert_before(t_list *list, t_lnode *position, void *data)
{
  t_lnode *node;

  node = xmalloc(sizeof(t_lnode));
  node->data = data;
  list_insert_node_before(list, position, node);
}

void
list_insert_after(t_list *list, t_lnode *position, void *data)
{
  t_lnode *node;

  node = xmalloc(sizeof(t_lnode));
  node->data = data;
  list_insert_node_after(list, position, node);
}

void
list_insert_node_before(t_list *list, t_lnode *position, t_lnode *node)
{
  node->prev = position->prev;
  node->next = position;
  if (position->prev)
    position->prev->next = node;
  else
    list->head = node;
  position->prev = node;
  list->size++;
}

void
list_insert_node_after(t_list *list, t_lnode *position, t_lnode *node)
{
  node->prev = position;
  node->next = position->next;
  if (position->next)
    position->next->prev = node;
  else
    list->tail = node;
  position->next = node;
  list->size++;
}

void
list_erase(t_list *list, t_lnode *position)
{
  if (list->head == position)
    list_pop_front(list);
  else if (list->tail == position)
    list_pop_back(list);
  else
    {
      position->prev->next = position->next;
      position->next->prev = position->prev;
      list->size--;
      if (list->f_delete)
	list->f_delete(position->data);
      free(position);
    }
}

void
list_swap(t_list *list_a, t_list *list_b)
{
  t_list tmp;

  memcpy(&tmp, list_a, sizeof(t_list));
  memcpy(list_a, list_b, sizeof(t_list));
  memcpy(list_b, &tmp, sizeof(t_list));
}

void
list_clear(t_list *list)
{
  t_lnode *w, *node;

  w = list->head;
  while (w != NULL)
    {
      node = w;
      w = w->next;
      list->f_delete(node->data);
      free(node);
    }
  list_full_init(list, list->f_delete, list->f_compare);
}

void
list_splice_before(t_list *list, t_lnode *position, t_list *src)
{
  if (list->head == position)
    {
      src->tail->next = position;
      position->prev = src->tail;
      list->head = src->head;
    }
  else
    {
      position->prev->next = src->head;
      src->head->prev = position->prev;
      src->tail->next = position;
      position->prev = src->tail;
    }
  list->size += src->size;
  list_full_init(src, src->f_delete, src->f_compare);
}

void
list_splice_after(t_list *list, t_lnode *position, t_list *src)
{
  if (list->tail == position)
    {
      position->next = src->head;
      src->head->prev = position;
      list->tail = src->tail;
    }
  else
    {
      position->next->prev = src->tail;
      src->tail->next = position->next;
      src->head->prev = position;
      position->next = src->head;
    }
  list->size += src->size;
  list_full_init(src, src->f_delete, src->f_compare);
}

void
list_remove(t_list *list, void *data)
{
  t_lnode *w, *node;

  w = list->head;
  while (w != NULL)
    {
      node = w;
      w = w->next;
      if (list->f_compare(node->data, data) == 0)
	list_erase(list, node);
    }
}

void
list_remove_if(t_list *list, int (*f_condition)(void *))
{
  t_lnode *w, *node;

  w = list->head;
  while (w != NULL)
    {
      node = w;
      w = w->next;
      if (f_condition(node->data) == 0)
	list_erase(list, node);
    }
}

void
list_unique(t_list *list)
{
  t_lnode *ref, *w, *node;

  ref = list->head;
  while (ref != NULL)
    {
      w = ref->next;
      while (w != NULL)
	{
	  node = w;
	  w = w->next;
	  if (list->f_compare(ref->data, node->data) == 0)
	    list_erase(list, node);
	}
      ref = ref->next;
    }
}

static t_lnode *
_list_extract_node(t_list *list, t_lnode *position)
{
  if (list->size == 1)
    {
      list_full_init(list, list->f_delete, list->f_compare);
      return (position);
    }
  if (list->head == position)
    {
      list->head->next->prev = NULL;
      list->head = list->head->next;
    }
  else if (list->tail == position)
    {
      list->tail->prev->next = NULL;
      list->tail = list->tail->prev;
    }
  list->size--;
  return (position);
}

t_lnode *
list_extract_node(t_list *list, t_lnode *position)
{
  (void)_list_extract_node(list, position);
  position->prev = NULL;
  position->next = NULL;
  return (position);
}

void
list_merge(t_list *list_a, t_list *list_b)
{
  t_lnode *w_a, *node;

  w_a = list_a->head;
  while (list_b->head != NULL)
    {
      while (w_a != NULL
	     && list_a->f_compare(w_a->data, list_b->head->data) <= 0)
	w_a = w_a->next;
      if (w_a == NULL)
	{
	  list_splice_after(list_a, list_a->tail, list_b);
	  break ;
	}
      node = _list_extract_node(list_b, list_b->head);
      list_insert_node_before(list_a, w_a, node);
      w_a = node;
    }
  list_full_init(list_b, list_b->f_delete, list_b->f_compare);
}

void
list_reverse(t_list *list)
{
  t_lnode *w, *node;
  void *tmp;

  w = list->head;
  while (w)
    {
      node = w;
      w = w->next;
      tmp = node->prev;
      node->prev = node->next;
      node->next = tmp;
    }
  node = list->head;
  list->head = list->tail;
  list->tail = node;
}

t_lnode *
list_find_node(t_list *list, void *f_compare_arg)
{
  t_lnode *w;

  w = list->head;
  while (w)
    {
      if (list->f_compare(f_compare_arg, w->data) == 0)
	return (w);
    }
  return (NULL);
}


static void _list_sort_swap_data(t_lnode *a, t_lnode *b)
{
  void *tmp;

  tmp = a->data;
  a->data = b->data;
  b->data = tmp;
}

void
list_sort_asc(t_list *list)
{
  t_lnode *w;
  int again;
    
  if (list->size < 2)
    return ;
  do
    {
      again = 0;
      for (w = list->head; w != NULL; w = w->next)
	{
	  if (list->f_compare(w, w->next) > 0) /* sort ASC */
	    {
	      _list_sort_swap_data(w, w->next);
	      again = 1;
	    }
	}
    } while (again != 0);
}

void
list_sort_desc(t_list *list)
{
  t_lnode *w;
  int again;

  if (list->size < 2)
    return ;
  do
    {
      again = 0;
      for (w = list->head; w != NULL; w = w->next)
	{
	  if (list->f_compare(w, w->next) < 0) /* sort DESC */
	    {
	      _list_sort_swap_data(w, w->next);
	      again = 1;
	    }
	}
    } while (again != 0);
}
