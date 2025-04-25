/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xlib.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:26:45 by teando            #+#    #+#             */
/*   Updated: 2025/04/25 16:54:50 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_LIB_H
#define RT_LIB_H

#include "libft.h"
#include "app.h"

t_list *xgc_init(t_app *app);
void *xmalloc(size_t size, t_app *app);
void *xcalloc(size_t n, size_t sz, t_app *app);
void xfree(void **p, t_app *app);

#endif
