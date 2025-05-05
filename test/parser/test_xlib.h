#ifndef TEST_XLIB_H
#define TEST_XLIB_H

#include "test.h"

typedef struct s_app t_app;

/* gc */
t_list *xgc_init(t_app *app);
void *xmalloc(size_t size, t_app *app);
void *xcalloc(size_t n, size_t sz, t_app *app);
void xfree(void **p);

/* xstr */
char *xstrdup(const char *s1, t_app *app);
char *xstrndup(const char *s, size_t n, t_app *app);
char **xsplit(char const *s, char c, t_app *app);
char *xstrtrim(char const *s1, char const *set, t_app *app);

/* fd */
int xopen(char *pathname, int flags, t_app *app);
int xclose(int *fd);

/* libft */
char *xget_next_line(int fd, t_app *app);
double ft_strtod(const char *nptr, char **endptr);

#endif