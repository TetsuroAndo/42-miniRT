/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:50:20 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/17 16:33:55 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_hit.h"

static void	fill_rec(t_hit_record *rec, t_obj *obj, t_ray ray, double t)
{
	rec->t = t;
	rec->pos = vec3_add(ray.orig, vec3_scale(ray.dir, t));
	rec->normal = vec3_normalize(vec3_sub(rec->pos, obj->u.sp.center));
	rec->color = obj->u.sp.color;
	rec->obj = obj;
}

static double	get_valid_t(const double a, const double b, const double disc)
{
	double	sqrt_d;
	double	t1;
	double	t2;

	sqrt_d = sqrt(disc);
	t1 = (-b - sqrt_d) / (2 * a);
	if (t1 >= 1e-6)
		return (t1);
	t2 = (-b + sqrt_d) / (2 * a);
	if (t2 >= 1e-6)
		return (t2);
	return (INFINITY);
}

static double	calc_sphere_hit(t_obj *obj, t_ray ray)
{
	const t_vec3	oc = vec3_sub(ray.orig, obj->u.sp.center);
	const double	a = vec3_dot(ray.dir, ray.dir);
	const double	b = 2.0 * vec3_dot(oc, ray.dir);
	const double	c = vec3_dot(oc, oc) - obj->u.sp.radius * obj->u.sp.radius;
	const double	disc = b * b - 4 * a * c;
	if (disc < 0.0)
		return (INFINITY);
	return (get_valid_t(a, b, disc));
}

t_hit_record	sphere_hit(t_obj *obj, t_ray ray, t_app *app)
{
	t_hit_record	rec;
	double			t;

	(void)app;
	rec = (t_hit_record){.t = INFINITY};
	t = calc_sphere_hit(obj, ray);
	if (t < INFINITY)
		fill_rec(&rec, obj, ray, t);
	return (rec);
}
