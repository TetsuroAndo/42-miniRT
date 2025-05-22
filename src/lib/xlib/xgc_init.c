/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xgc_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:41:54 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 20:25:14 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"

t_list	*xgc_init(t_app *app)
{
	t_list	*node;

	node = ft_gc_init();
	if (!node)
		exit_app(app, E_ALLOC);
	return (node);
}
