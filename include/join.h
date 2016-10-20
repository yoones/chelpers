#ifndef JOIN_H_
# define JOIN_H_

char *
join_from_list(t_list *list, char separator);

char *
join_from_list_at(t_list *list, char separator, int skip);

char *
join_from_array(char **arr, char separator);

#endif
