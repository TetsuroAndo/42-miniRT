/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 06:25:13 by teando            #+#    #+#             */
/*   Updated: 2025/05/20 07:09:56 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_cam.h"

void	move_key_hook(int keycode, t_app *app)
{
	t_vec3	forward;
	t_vec3	right;

	forward = vec3_normalize(app->scene->cam.dir);
	right = vec3_normalize(vec3_cross(forward, vec3_new(0, 1, 0)));
	if (keycode == KEY_W)
		cam_translate(&app->scene->cam, vec3_scale(forward, MOVE_STEP));
	if (keycode == KEY_S)
		cam_translate(&app->scene->cam, vec3_scale(forward, -MOVE_STEP));
	if (keycode == KEY_A)
		cam_translate(&app->scene->cam, vec3_scale(right, -MOVE_STEP));
	if (keycode == KEY_D)
		cam_translate(&app->scene->cam, vec3_scale(right, MOVE_STEP));
	if (keycode == KEY_R)
		cam_translate(&app->scene->cam, vec3_scale(vec3_new(0, 1, 0),
				MOVE_STEP));
	if (keycode == KEY_F)
		cam_translate(&app->scene->cam, vec3_scale(vec3_new(0, 1, 0),
				-MOVE_STEP));
}

void	rot_key_hook(int keycode, t_app *app)
{
	if (keycode == KEY_LEFT)
		cam_rotate_yaw(&app->scene->cam, ROT_STEP);
	if (keycode == KEY_RIGHT)
		cam_rotate_yaw(&app->scene->cam, -ROT_STEP);
	if (keycode == KEY_UP)
		cam_rotate_pitch(&app->scene->cam, ROT_STEP);
	if (keycode == KEY_DOWN)
		cam_rotate_pitch(&app->scene->cam, -ROT_STEP);
}
