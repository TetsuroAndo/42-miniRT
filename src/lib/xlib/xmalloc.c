/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:27:21 by teando            #+#    #+#             */
/*   Updated: 2025/05/15 22:48:29 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "xlib.h"

void *xmalloc(size_t size, t_app *app)
{
	void *p;

	p = ft_gc_malloc(app->gc, size);
	if (!p)
		exit_app(app, E_ALLOC);
	return (p);
}
