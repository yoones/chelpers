#ifndef LIST_H_
# define LIST_H_

struct s_lnode
{
  void *data;
  struct s_lnode *prev;
  struct s_lnode *next;
};

typedef struct s_lnode t_lnode;

struct s_list
{
  t_lnode *head;
  t_lnode *tail;
  size_t size;
  void (*f_delete)(void *);
  int (*f_compare)(void *, void *);
};

typedef struct s_list t_list;

void list_init(t_list *list);
void list_full_init(t_list *list, void (*f_delete)(void *), int (*f_compare)(void *, void *));
void list_set_f_no_delete(t_list *list);
void list_set_f_delete(t_list *list, void (*f_delete)(void *));
void list_reset_f_compare(t_list *list);
void list_set_f_compare(t_list *list, int (*f_comapre)(void *, void *));
void list_assign(t_list *list, t_lnode *head, t_lnode *tail);
void list_push_front(t_list *list, void *data);
void list_pop_front(t_list *list);
void list_push_back(t_list *list, void *data);
void list_pop_back(t_list *list);
void list_insert_before(t_list *list, t_lnode *position, void *data);
void list_insert_after(t_list *list, t_lnode *position, void *data);
void list_insert_node_before(t_list *list, t_lnode *position, t_lnode *node);
void list_insert_node_after(t_list *list, t_lnode *position, t_lnode *node);
void list_erase(t_list *list, t_lnode *position);
void list_swap(t_list *list_a, t_list *list_b);
void list_clear(t_list *list);
void list_splice_before(t_list *list, t_lnode *position, t_list *src);
void list_splice_after(t_list *list, t_lnode *position, t_list *src);
void list_remove(t_list *list, void *data);
void list_remove_if(t_list *list, int (*f_condition)(void *));
void list_unique(t_list *list);
t_lnode * list_extract_node(t_list *list, t_lnode *position);
void list_merge(t_list *list_a, t_list *list_b);
void list_reverse(t_list *list);

#endif
