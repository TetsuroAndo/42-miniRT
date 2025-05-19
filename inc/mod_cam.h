/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_cam.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 05:31:00 by teando            #+#    #+#             */
/*   Updated: 2025/05/20 07:10:07 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_CAM_H
#define MOD_CAM_H

#include "rt_scene.h"
#include "rt_vec.h"
#include "xlib.h"

#define KEY_A 97
#define KEY_D 100
#define KEY_F 102
#define KEY_R 114
#define KEY_S 115
#define KEY_W 119
#define KEY_LEFT 65361
#define KEY_UP 65362
#define KEY_RIGHT 65363
#define KEY_DOWN 65364

/* 5deg (M_PI / 36.0) */
#define ROT_STEP 0.087266
#define MOVE_STEP 1.0

/* key */
void	move_key_hook(int keycode, t_app *app);
void	rot_key_hook(int keycode, t_app *app);

/* move */
void	cam_translate(t_camera *cam, t_vec3 delta);
void	cam_rotate_yaw(t_camera *cam, double rad);
void cam_rotate_pitch(t_camera *cam, double rad);

/* utils */
t_vec3 vec3_rotate(t_vec3 v, t_vec3 axis, double angle);

#endif
