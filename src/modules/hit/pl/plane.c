/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:12:32 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/18 17:30:55 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_hit.h"

static void	fill_plane_hit_record(t_hit_record *rec, t_obj *obj, t_ray ray)
{
	rec->pos = vec3_add(ray.orig, vec3_scale(ray.dir, rec->t));
	rec->obj = obj;
	rec->normal = obj->u.pl.normal;
	rec->color = obj->u.pl.color;
}

t_hit_record	plane_hit(t_obj *obj, t_ray ray, t_app *app)
{
	t_hit_record	result;
	double			denom;
	t_vec3			diff;
	t_plane			pl;

	(void)app;
	pl = obj->u.pl;
	result.t = -1.0;
	denom = vec3_dot(ray.dir, obj->u.pl.normal);
	if (fabs(denom) < EPSILON)
		return (result);
	diff = vec3_sub(pl.point, ray.orig);
	result.t = vec3_dot(diff, pl.normal) / denom;
	if (result.t < 0)
		result.t = -1.0;
	fill_plane_hit_record(&result, obj, ray);
	return (result);
}
