/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:47:56 by teando            #+#    #+#             */
/*   Updated: 2025/05/09 03:20:49 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_app	*init_app(void)
{
	t_app *app;

	app = (t_app *)ft_calloc(sizeof(t_app), 1);
	if (!app)
		exit(1);
	app->gc = xgc_init(app);
	app->img = ft_calloc(sizeof(t_img), 1);
	if (!app->img)
		exit_app(app, 1);
	return (app);
}
