#include <string.h>
#include "xfunctions.h"
#include "list.h"
#include "join.h"

char *
join_from_list(t_list *list, char separator)
{
  return (join_from_list_at(list, separator, 0));
}

char *
join_from_list_at(t_list *list, char separator, int skip)
{
  int length;
  t_lnode *w;
  char *str, *tmp;
  int i;

  if (list->size == 0)
    return (xstrdup(""));
  length = 0;
  w = list->head;
  for (i = 0; i < skip && w; i++)
    w = w->next;
  for (; w != NULL; w = w->next)
    length += strlen(w->data);
  length += list->size - 1;
  str = xmalloc(sizeof(char) * (length + 1));
  tmp = str;
  w = list->head;
  for (i = 0; i < skip && w; i++)
    w = w->next;
  for (; w->next != NULL; w = w->next)
    {
      length = strlen(w->data);
      memcpy(tmp, w->data, length);
      tmp[length] = separator;
      tmp += length + 1;
    }
  length = strlen(w->data);
  memcpy(tmp, w->data, length);
  tmp[length] = '\0';
  return (str);
}

char *
join_from_array(char **arr, char separator)
{
  int length;
  char *str, *tmp;
  int i;
  
  if (arr[0] == NULL)
    return (xstrdup(""));
  length = 0;
  for (i = 0; arr[i]; i++)
    length += strlen(arr[i]) + 1;
  length -= 1;
  str = xmalloc(sizeof(char) * (length + 1));
  tmp = str;
  for (i = 0; arr[i + 1] != NULL; i++)
    {
      length = strlen(arr[i]);
      memcpy(tmp, arr[i], length);
      tmp[length] = separator;
      tmp += length + 1;
    }
  length = strlen(arr[i]);
  memcpy(tmp, arr[i], length);
  tmp[length] = '\0';
  return (str);
}
