/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xlib.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:26:45 by teando            #+#    #+#             */
/*   Updated: 2025/04/30 19:06:48 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XLIB_H
# define XLIB_H

# include "app.h"
# include "libft.h"

typedef struct s_app	t_app;

t_list					*xgc_init(t_app *app);
void					*xmalloc(size_t size, t_app *app);
void					*xcalloc(size_t n, size_t sz, t_app *app);
void					xfree(void **p, t_app *app);

// xstr
char					*xstrdup(const char *s1, t_app *app);
char					*xstrndup(const char *s, size_t n, t_app *app);
char					**xsplit(char const *s, char c, t_app *app);

// libft?
double					ft_strtod(const char *nptr, char **endptr);

#endif
