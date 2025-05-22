/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xlib.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:26:45 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 20:41:05 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XLIB_H
# define XLIB_H

# ifdef TEST_MODE
#  include "../test/parser/test_app.h"
# else
#  include "app.h"
# endif

# include "err.h"
# include "libft.h"
# include "rt_vec.h"
# include <errno.h>

typedef struct s_app	t_app;

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

t_list					*xgc_init(t_app *app);
void					*xmalloc(size_t size, t_app *app);
void					*xcalloc(size_t n, size_t sz, t_app *app);
void					xfree(void **p, t_app *app);

char					*xstrdup(const char *s1, t_app *app);
char					*xstrndup(const char *s, size_t n, t_app *app);
char					**xsplit(char const *s, char c, t_app *app);
char					*xstrtrim(char const *s1, char const *set, t_app *app);

int						xopen(char *pathname, int flags, t_app *app);
int						xclose(int *fd);

char					*xget_next_line(int fd, t_app *app);
double					ft_strtod(const char *nptr, char **endptr);

t_vec3					vec3_cross(t_vec3 v1, t_vec3 v2);
double					vec3_len(t_vec3 v);
t_vec3					vec3_normalize(t_vec3 v);
t_vec3					vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3					vec3_mul(t_vec3 v1, t_vec3 v2);
t_vec3					vec3_new(double x, double y, double z);
t_vec3					vec3_scale(t_vec3 v, double s);
void					vec3_print(t_vec3 v);
t_vec3					vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3					vec3_div(t_vec3 v, double t);
double					vec3_dot(t_vec3 a, t_vec3 b);
t_vec3					vec3_negate(t_vec3 v);

void					debug_print_scene(t_app *app);

#endif
