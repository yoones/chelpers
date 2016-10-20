#ifndef XFUNCTIONS_H_
# define XFUNCTIONS_H_

void *xmalloc(size_t size);
void xfree(void *ptr);
void *xcalloc(size_t nmemb, size_t size);
void *xrealloc(void *ptr, size_t size);

char *xstrdup(const char *s);
char *xstrndup(const char *s, size_t n);

#endif
