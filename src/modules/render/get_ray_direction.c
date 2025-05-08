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

t_cam_basis	init_cam_basis(t_camera *cam)
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
	t_vec3	dir;
	t_vec3	forward;
	
	forward = vec3_vec3_normalize(cam->dir);
	dir = vec3_add(add_f_m(cam, forward, i), mul_up_y(cam, forward, j));
	return (vec3_vec3_normalize(dir));
}
