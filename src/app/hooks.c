/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:25:14 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/08 21:17:07 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

#define KEY_ESC 65307

static int	close_window(t_app *app)
{
	exit_app(app, 0);
	return (0);
}

static int	key_hook(int keycode, t_app *app)
{
	if (keycode == KEY_ESC)
		exit_app(app, 0);
	return (0);
}

void	setup_hooks(t_app *app)
{
	mlx_hook(app->win, 2, 1L << 0, key_hook, app);
	mlx_hook(app->win, 17, 0, close_window, app);
}