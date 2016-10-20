#ifndef SPLIT_H_
# define SPLIT_H_

void
split_in_list(char *str, char *separators, t_list *list);

char **
split_in_array(char *str, char *separators);

#endif
