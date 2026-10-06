
#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>

char *ft_strchr(char *s, int c)
{
    while(*s != (char)c)
    {
        if (!*s)
        {
            return 0;
        }
        s++;
    }
    return (char* )s;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    char* d = (char *) dest;
    const char *s = (const char *)src;
    size_t i = 0;
    while(i < n)
    {
        d[i] = s[i];
        i++;
    }
    return dest;
}

size_t ft_strlen(char *s)
{
    ssize_t i = 0;
    while (s[i]) {
        i++;
    }
    return i;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1;
    if (*s1)
        size1 = ft_strlen(*s1);
    else
        size1 = 0;

    char *tmp = malloc(size2 + size1 + 1);
    if (!tmp)
        return 0;

    if(*s1)
        ft_memcpy(tmp, *s1, size1);
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';

    free(*s1);
    *s1 = tmp;
    return 1;
}

int str_append_str(char **s1, char *s2)
{
  return str_append_mem(s1, s2, ft_strlen(s2));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
    if(!dest || !src)
        return NULL;
    if (dest < src)
        return ft_memcpy(dest, src, n);

    char* d = (char *) dest;
    const char* s = ((const char *) src);
    if (dest > src)
    {
        size_t i = n;
        while (i > 0)
        {
            d[i -1] = s[i -1];
            i--;
        }
    }
    return dest;
}

char *get_next_line(int fd)
{
  static char b[BUFFER_SIZE + 1] = "";
  char *ret = NULL;
  char *tmp = ft_strchr(b, '\n');
  while(!tmp)
  {
    if (!str_append_str(&ret, b))
      return (NULL);
    int read_ret = read(fd, b, BUFFER_SIZE);
    if (read_ret == -1)
      return (NULL);
    b[read_ret] = 0;
  }
  if (!str_append_mem(&ret, b, tmp - b + 1))
  {
    free(ret);
    return NULL;
  }
  return ret;
}
