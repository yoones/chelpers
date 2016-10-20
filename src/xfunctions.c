#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "print_error_and_abort.h"
#include "list.h"

void *
xmalloc(size_t size)
{
  void *ptr;

  ptr = malloc(size);
  if (!ptr)
    print_error_and_abort("malloc");
  return (ptr);
}

void
xfree(void *ptr)
{
  free(ptr);
}

void *
xcalloc(size_t nmemb, size_t size)
{
  void *ptr;

  ptr = calloc(nmemb, size);
  if (!ptr)
    print_error_and_abort("calloc");
  return (ptr);
}

void *
xrealloc(void *ptr, size_t size)
{
  ptr = realloc(ptr, size);
  if (!ptr)
    print_error_and_abort("realloc");
  return (ptr);
}

char *
xstrdup(const char *s)
{
  char *ptr;

  ptr = strdup(s);
  if (!ptr)
    print_error_and_abort("strdup");
  return (ptr);
}

char *
xstrndup(const char *s, size_t n)
{
  char *ptr;

  ptr = strndup(s, n);
  if (!ptr)
    print_error_and_abort("strndup");
  return (ptr);
}
