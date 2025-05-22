/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:51:37 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/22 20:43:00 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_hit.h"

void				cy_check_side(t_hit_record *hit, t_obj *obj, t_ray ray,
						t_vec3 axis);
void				cy_try_cap(t_hit_record *hit, t_obj *obj, t_ray ray,
						t_vec3 cap_dir);

void	cy_set_record(t_hit_record *rec, t_obj *obj, t_vec3 pos, double t)
{
	rec->t = t;
	rec->pos = pos;
	rec->color = obj->u_type.cy.color;
	rec->obj = obj;
}

void	cy_apply_face_orientation(t_hit_record *rec, t_ray ray)
{
	if (vec3_dot(rec->normal, ray.dir) > 0)
		rec->normal = vec3_scale(rec->normal, -1.0);
}

static inline void	cy_check_caps(t_hit_record *hit, t_obj *obj, t_ray ray,
		t_vec3 axis)
{
	cy_try_cap(hit, obj, ray, axis);
	cy_try_cap(hit, obj, ray, vec3_scale(axis, -1.0));
}

t_hit_record	cylinder_hit(t_obj *obj, t_ray ray, t_app *app)
{
	t_hit_record	hit;
	t_vec3			axis;

	(void)app;
	hit.t = -1.0;
	axis = vec3_normalize(obj->u_type.cy.axis);
	cy_check_side(&hit, obj, ray, axis);
	cy_check_caps(&hit, obj, ray, axis);
	return (hit);
}
