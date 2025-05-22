/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_cam.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 05:31:00 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 20:29:46 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_CAM_H
# define MOD_CAM_H

# include "rt_scene.h"
# include "rt_vec.h"
# include "xlib.h"

# define KEY_A 97
# define KEY_D 100
# define KEY_S 115
# define KEY_W 119
# define KEY_SHIFT 65505
# define KEY_SPACE 32

# define KEY_F 102
# define KEY_R 114
# define KEY_X 120
# define KEY_Z 122

# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364

# define ROT_STEP 0.087266
# define MOVE_STEP 1.0

void	move_key_hook(int keycode, t_app *app);
void	up_down_key_hook(int keycode, t_app *app);
void	rot_key_hook(int keycode, t_app *app);

void	cam_translate(t_camera *cam, t_vec3 delta);
void	cam_rotate_yaw(t_camera *cam, double rad);
void	cam_rotate_pitch(t_camera *cam, double rad);

t_vec3	vec3_rotate(t_vec3 v, t_vec3 axis, double angle);

#endif
