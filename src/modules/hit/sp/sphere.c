/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:50:20 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/22 20:49:24 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_hit.h"

static inline void	fill_rec(t_hit_record *rec, t_obj *obj, t_ray ray, double t)
{
	rec->t = t;
	rec->pos = vec3_add(ray.orig, vec3_scale(ray.dir, t));
	/* 法線を求める (pos - center) / r */
	rec->normal = vec3_normalize(vec3_sub(rec->pos, obj->u_type.sp.center));
	/* レイが球の内側から出て行く場合は外向きに反転させる */
	if (vec3_dot(ray.dir, rec->normal) > 0.0)
		rec->normal = vec3_scale(rec->normal, -1.0);
	rec->color = obj->u_type.sp.color;
	rec->obj = obj;
}

static inline double	get_valid_t(double a, double b, double disc)
{
	const double	sqrt_d = sqrt(disc);
	const double	t1 = (-b - sqrt_d) / (2 * a);
	const double	t2 = (-b + sqrt_d) / (2 * a);

	if (t1 > EPSILON)
		return (t1); /* 手前側ヒット */
	if (t2 > EPSILON)
		return (t2); /* 内部にいた場合など */
	return (-1.0);
}

static inline double	solve_quadratic(const t_vec3 oc, const t_vec3 dir,
		const double r2)
{
	const double	a = vec3_dot(dir, dir);
	const double	b = 2.0 * vec3_dot(oc, dir);
	const double	c = vec3_dot(oc, oc) - r2;
	const double	disc = b * b - 4.0 * a * c;

	if (disc < 0.0)
		return (-1.0);
	return (get_valid_t(a, b, disc));
}

t_hit_record	sphere_hit(t_obj *obj, t_ray ray, t_app *app)
{
	t_hit_record	rec;
	double			t;
	const t_vec3	oc = vec3_sub(ray.orig, obj->u_type.sp.center);

	(void)app;
	rec.t = -1.0; /* ヒットなしで初期化 */
	t = solve_quadratic(oc, ray.dir, obj->u_type.sp.radius
			* obj->u_type.sp.radius);
	if (t > 0.0)
		fill_rec(&rec, obj, ray, t);
	return (rec);
}
