/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 05:32:00 by teando            #+#    #+#             */
/*   Updated: 2025/05/20 06:07:15 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_cam.h"
#include "xlib.h"
#include <math.h>

void	cam_translate(t_camera *cam, t_vec3 delta)
{
	cam->pos = vec3_add(cam->pos, delta);
}

void	cam_rotate_yaw(t_camera *cam, double rad)
{
	cam->dir = vec3_rotate(cam->dir, (t_vec3){0, 1, 0}, rad);
}

void	cam_rotate_pitch(t_camera *cam, double rad)
{
	t_vec3 right = vec3_normalize(vec3_cross(cam->dir, (t_vec3){0, 1, 0}));
	cam->dir = vec3_rotate(cam->dir, right, rad);
}
