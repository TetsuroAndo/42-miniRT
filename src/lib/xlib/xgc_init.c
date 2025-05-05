/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xgc_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:41:54 by teando            #+#    #+#             */
/*   Updated: 2025/05/05 09:57:17 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"

t_list *xgc_init(t_app *app)
{
	t_list *node;

	node = ft_gc_init();
    if (!node)
		exit_app(app, E_ALLOC);
    return (node);
}
