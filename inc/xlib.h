/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xlib.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:26:45 by teando            #+#    #+#             */
/*   Updated: 2025/05/06 14:59:41 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XLIB_H
# define XLIB_H

# include "err.h"
# include "libft.h"
# include <errno.h>

# ifdef TEST_MODE
#  include "../test/parser/test_app.h"
# else
#  include "app.h"
# endif

typedef struct s_app	t_app;

/* gc */
t_list					*xgc_init(t_app *app);
void					*xmalloc(size_t size, t_app *app);
void					*xcalloc(size_t n, size_t sz, t_app *app);
void					xfree(void **p, t_app *app);

/* xstr */
char					*xstrdup(const char *s1, t_app *app);
char					*xstrndup(const char *s, size_t n, t_app *app);
char					**xsplit(char const *s, char c, t_app *app);
char					*xstrtrim(char const *s1, char const *set, t_app *app);

/* fd */
int						xopen(char *pathname, int flags, t_app *app);
int						xclose(int *fd);

/* libft */
char					*xget_next_line(int fd, t_app *app);
double					ft_strtod(const char *nptr, char **endptr);

/* core */
void					exit_app(t_app *app, int code);
void					exit_errmsg(char *msg, t_app *app);

#endif
