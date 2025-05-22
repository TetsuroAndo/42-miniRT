/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:47:56 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 20:47:39 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_app	*init_app(void)
{
	t_app	*app;

	app = (t_app *)ft_calloc(sizeof(t_app), 1);
	if (!app)
		exit(1);
	app->gc = xgc_init(app);
	app->img = ft_calloc(sizeof(t_img), 1);
	if (!app->img)
		exit_app(app, 1);
	return (app);
}
