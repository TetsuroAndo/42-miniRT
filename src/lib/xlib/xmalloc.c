/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:27:21 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 20:25:21 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"

void	*xmalloc(size_t size, t_app *app)
{
	void	*p;

	p = ft_gc_malloc(app->gc, size);
	if (!p)
		exit_app(app, E_ALLOC);
	return (p);
}
