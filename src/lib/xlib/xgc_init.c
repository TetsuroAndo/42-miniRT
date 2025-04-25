/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xgc_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:41:54 by teando            #+#    #+#             */
/*   Updated: 2025/04/25 15:43:22 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_list *xgc_init(t_app *app)
{
	t_list *node;

	node = ft_gc_init();
    if (!node)
		exit_app(app, E_ALLOC);
    return (node);
}
