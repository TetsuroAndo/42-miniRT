/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:48:53 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/08 21:03:37 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include <math.h>

typedef struct s_cam_basis
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	double	half_w;
	double	half_h;
}	t_cam_basis;


static t_vec3 vec3_scale(t_vec3 v, double s)
{
	t_vec3 result;

	result.x = v.x * s;
	result.y = v.y * s;
	result.z = v.z * s;
	return result;
}

static t_cam_basis	init_cam_basis(t_camera *cam)
{
	t_cam_basis		basis;
	double			aspect;
	double			theta;
	const t_vec3	world_up = vec3_new(0, 1, 0);

	basis.forward = vec3_normalize(cam->dir);
	basis.right = vec3_normalize(vec3_cross(basis.forward, world_up));
	basis.up = vec3_cross(basis.right, basis.forward);
	aspect = (double)WIDTH / (double)HEIGHT;
	theta = cam->fov * M_PI / 180.0;
	basis.half_h = tan(theta / 2.0);
	basis.half_w = aspect * basis.half_h;
	return (basis);
}

t_vec3	get_ray_direction(t_camera *cam, int i, int j)
{
	double		u;
	double		v;
	t_vec3		pixel_dir;
	t_cam_basis	basis;

	basis = init_cam_basis(cam);

	u = ((double)i + 0.5) / (double)WIDTH;
	v = ((double)j + 0.5) / (double)HEIGHT;
	u = (2.0 * u - 1.0) * basis.half_w;
	v = (1.0 - 2.0 * v) * basis.half_h;

	pixel_dir = vec3_add(basis.forward,
					vec3_add(vec3_scale(basis.right, u),
							 vec3_scale(basis.up, v)));
	return vec3_normalize(pixel_dir);
}