#ifndef LIBASM_H
#define LIBASM_H

#include <stddef.h>  // for size_t
#include <sys/types.h>  // for ssize_t
#include <errno.h>  // for errno
#include <stdlib.h>  // for malloc, free

size_t ft_strlen(const char *str);
char *ft_strcpy(char *dest, const char *src);
int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
char *ft_strdup(const char *str);

#endif
