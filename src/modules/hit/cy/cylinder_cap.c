/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:48:06 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 20:43:00 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_hit.h"

void					cy_set_record(t_hit_record *rec, t_obj *obj, t_vec3 pos,
							double t);
void					cy_apply_face_orientation(t_hit_record *rec, t_ray ray);

static inline int	cy_cap_valid(t_vec3 hit, t_vec3 center, double r)
{
	return (vec3_len(vec3_sub(hit, center)) <= r + EPSILON * 10);
}

static inline double	cy_cap_t(t_ray ray, t_vec3 center, t_vec3 axis)
{
	double	denom;

	denom = vec3_dot(ray.dir, axis);
	if (fabs(denom) <= EPSILON)
		return (-1.0);
	return (vec3_dot(vec3_sub(center, ray.orig), axis) / denom);
}

void	cy_try_cap(t_hit_record *hit, t_obj *obj, t_ray ray, t_vec3 cap_dir)
{
	t_vec3	center;
	t_vec3	pos;
	t_vec3	axis;
	double	t;
	double	sign;

	if (vec3_len(cap_dir) > 0)
		sign = 1.0;
	else
		sign = -1.0;
	axis = vec3_normalize(cap_dir);
	center = vec3_add(obj->u_type.cy.center, vec3_scale(axis, sign * obj->u_type.cy.height
				* 0.5));
	t = cy_cap_t(ray, center, axis);
	if (t <= EPSILON || (hit->t > 0 && t >= hit->t))
		return ;
	pos = vec3_add(ray.orig, vec3_scale(ray.dir, t));
	if (!cy_cap_valid(pos, center, obj->u_type.cy.radius))
		return ;
	cy_set_record(hit, obj, pos, t);
	hit->normal = vec3_scale(axis, sign);
	cy_apply_face_orientation(hit, ray);
}
