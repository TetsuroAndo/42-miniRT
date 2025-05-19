/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:25:14 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/20 06:32:03 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"
#include "mod_cam.h"
#include "mod_render.h"

#define KEY_ESC 65307

static inline int	close_window(t_app *app)
{
	exit_app(app, 0);
	return (0);
}

static inline int	ctl_key_hook(int keycode, t_app *app)
{
	if (keycode == KEY_ESC)
		exit_app(app, 0);
	if (keycode >= KEY_A && keycode <= KEY_W)
		move_key_hook(keycode, app);
	if (keycode >= KEY_LEFT && keycode <= KEY_DOWN)
		rot_key_hook(keycode, app);
	app->dirty = 1;
	return (0);
}

void	setup_hooks(t_app *app)
{
	mlx_hook(app->win, 2, 1L << 0, ctl_key_hook, app);
	mlx_hook(app->win, 17, 0, close_window, app);
	mlx_loop_hook(app->mlx, redraw_loop, app);
}
