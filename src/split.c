#include <string.h>
#include "list.h"
#include "xfunctions.h"

static inline int
_is_separator(char *separators, char c)
{
  register int i;

  for (i = 0; separators[i]; i++)
    {
      if (separators[i] == c)
	return (i);
    }
  return (-1);
}

static inline int
_get_word_length(char *str, char *separators)
{
  register int i;

  i = 0;
  while (str[i] && _is_separator(separators, str[i]) == -1)
    i++;
  return (i);
}

static inline void
_skip_separators(char **str, char *separators)
{
  while (_is_separator(separators, **str) >= 0)
    (*str)++;
}

void
split_in_list(char *str, char *separators, t_list *list)
{
  int word_length;
  char *word;
  
  while (*str)
    {
      _skip_separators(&str, separators);
      word_length = _get_word_length(str, separators);
      if (word_length == 0)
	return ;
      word = xstrndup(str, word_length);
      list_push_back(list, word);
      str += word_length;
    }
}

char **
split_in_array(char *str, char *separators)
{
  t_list list;
  char **arr;
  register unsigned int i;
  t_lnode *w;
  
  list_init(&list);
  list_set_f_no_delete(&list);
  split_in_list(str, separators, &list);
  arr = xmalloc(sizeof(char *) * (list.size + 1));
  for (i = 0, w = list.head; i < list.size; i++, w = w->next)
    arr[i] = w->data;
  arr[i] = NULL;
  list_clear(&list);
  return (arr);
}
