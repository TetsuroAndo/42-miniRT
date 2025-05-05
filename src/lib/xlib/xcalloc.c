/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xcalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:36:59 by teando            #+#    #+#             */
/*   Updated: 2025/05/05 09:57:36 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "xlib.h"

void *xcalloc(size_t n, size_t sz, t_app *app)
{
    void *p;

	p = ft_gc_calloc(app->gc, n, sz);
    if (!p)
		exit_app(app, E_ALLOC);
    return (p);
}
