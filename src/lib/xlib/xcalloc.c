/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xcalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:36:59 by teando            #+#    #+#             */
/*   Updated: 2025/05/08 14:18:18 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "app.h"
# include "xlib.h"

void *xcalloc(size_t n, size_t sz, t_app *app)
{
    void *p;

	p = ft_gc_calloc(app->gc, n, sz);
    if (!p)
		exit_app(app, 1);
    return (p);
}
