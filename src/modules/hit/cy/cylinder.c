/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:51:37 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/20 07:49:40 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   cylinder.c                                                               */
/* ************************************************************************** */

#include "mod_hit.h"

/* キャップ計算 */
typedef struct s_cap_data
{
	t_vec3	center;
	double	radius;
	double	t;
	t_vec3	normal;
}	t_cap_data;

typedef struct s_cap_params
{
	t_vec3	axis;
	double	radius;
	double	height;
	int		is_top;
}	t_cap_params;


/* ───────────────────────── ヘルパ ───────────────────────── */

static inline double	get_valid_t(double a, double b, double disc)
{
	const double	sqrt_d = sqrt(disc);
	const double	t1 = (-b - sqrt_d) / (2.0 * a);
	const double	t2 = (-b + sqrt_d) / (2.0 * a);

	if (t1 > EPSILON)
		return (t1);
	if (t2 > EPSILON)
		return (t2);
	return (-1.0);
}

static inline double	solve_quadratic(double a, double b, double c)
{
	const double	disc = b * b - 4.0 * a * c;

	if (disc < 0.0)
		return (-1.0);
	return (get_valid_t(a, b, disc));
}

static t_vec3	calculate_side_normal(t_vec3 hit_pos, t_vec3 center, t_vec3 axis)
{
	t_vec3	center_to_hit;
	t_vec3	radial;
	double	proj;

	center_to_hit = vec3_sub(hit_pos, center);
	proj = vec3_dot(center_to_hit, axis);
	radial = vec3_sub(center_to_hit, vec3_scale(axis, proj));
	return (vec3_normalize(radial));
}

static inline void	fill_record_side(t_hit_record *rec, t_obj *obj,
					t_ray ray, t_vec3 hit_data[3])
{
	rec->t = hit_data[0].x;
	rec->pos = hit_data[1];
	/* 側面の法線を求める */
	rec->normal = calculate_side_normal(hit_data[1], obj->u.cy.center, hit_data[2]);
	/* レイが円柱の内側から出て行く場合は外向きに反転させる */
	if (vec3_dot(rec->normal, ray.dir) > 0)
		rec->normal = vec3_scale(rec->normal, -1.0);
	rec->color = obj->u.cy.color;
	rec->obj = obj;
}

static inline void	fill_record_cap(t_hit_record *rec, t_obj *obj,
					t_ray ray, t_vec3 hit_data[3])
{
	rec->t = hit_data[0].x;
	rec->pos = hit_data[1];
	rec->normal = hit_data[2];
	/* レイが円柱の内側から出て行く場合は外向きに反転させる */
	if (vec3_dot(rec->normal, ray.dir) > 0)
		rec->normal = vec3_scale(rec->normal, -1.0);
	rec->color = obj->u.cy.color;
	rec->obj = obj;
}

/* ───────────────────────── 側面交差計算 ───────────────────────── */

static t_vec3	get_perpendicular_vectors(t_ray ray, const t_vec3 axis)
{
	t_vec3	result;
	double	d_dot_a;

	d_dot_a = vec3_dot(ray.dir, axis);
	result = vec3_sub(ray.dir, vec3_scale(axis, d_dot_a));
	return (result);
}

static t_vec3	get_oc_perpendicular(t_vec3 oc, const t_vec3 axis)
{
	double	oc_dot_a;
	t_vec3	result;

	oc_dot_a = vec3_dot(oc, axis);
	result = vec3_sub(oc, vec3_scale(axis, oc_dot_a));
	return (result);
}

static double	get_side_quadratic_params(t_vec3 d_perp, t_vec3 oc_perp,
					double radius, double quad_params[3])
{
	double	t_side;

	quad_params[0] = vec3_dot(d_perp, d_perp);
	if (fabs(quad_params[0]) < EPSILON)
		return (-1.0); /* レイが軸と平行 */
	quad_params[1] = 2.0 * vec3_dot(d_perp, oc_perp);
	quad_params[2] = vec3_dot(oc_perp, oc_perp) - radius * radius;
	t_side = solve_quadratic(quad_params[0], quad_params[1], quad_params[2]);
	return (t_side);
}

static t_hit_record	check_side_intersection(t_obj *obj, t_ray ray,
	const t_vec3 axis, const double params[2],
	t_vec3 d_perp, t_vec3 oc_perp)
{
	t_hit_record	hit;
	t_vec3			hit_data[3];
	double			quad_params[3];
	double			t_side;
	double			m;

	hit.t = -1.0;
	t_side = get_side_quadratic_params(d_perp, oc_perp, params[0], quad_params);
	if (t_side > EPSILON)
	{
		hit_data[1] = vec3_add(ray.orig, vec3_scale(ray.dir, t_side));
		m = vec3_dot(vec3_sub(hit_data[1], obj->u.cy.center), axis);
		if (m >= -params[1] / 2.0 && m <= params[1] / 2.0)
		{
			hit_data[0].x = t_side;
			hit_data[2] = axis;
			fill_record_side(&hit, obj, ray, hit_data);
		}
	}
	return (hit);
}

static t_hit_record	check_side_hit(t_obj *obj, t_ray ray,
					const t_vec3 axis, const double params[2])
{
	t_hit_record	hit;
	t_vec3			oc;
	t_vec3			d_perp;
	t_vec3			oc_perp;

	hit.t = -1.0;
	oc = vec3_sub(ray.orig, obj->u.cy.center);
	d_perp = get_perpendicular_vectors(ray, axis);
	oc_perp = get_oc_perpendicular(oc, axis);
	hit = check_side_intersection(obj, ray, axis, params, d_perp, oc_perp);
	return (hit);
}

/* ───────────────────────── キャップ交差計算 ───────────────────────── */

static t_vec3	get_cap_center(t_obj *obj, const t_vec3 axis,
				double height, int is_top)
{
	t_vec3	center;
	double	scale;

	scale = height / 2.0;
	if (is_top)
		center = vec3_add(obj->u.cy.center, vec3_scale(axis, scale));
	else
		center = vec3_sub(obj->u.cy.center, vec3_scale(axis, scale));
	return (center);
}

static double	get_cap_t(t_vec3 cap_center, t_ray ray,
				const t_vec3 axis)
{
	double	t;
	double	denom;

	denom = vec3_dot(ray.dir, axis);
	if (fabs(denom) <= EPSILON)
		return (-1.0);
	t = vec3_dot(vec3_sub(cap_center, ray.orig), axis) / denom;
	return (t);
}

static void	process_cap_hit(t_hit_record *hit, t_obj *obj, t_ray ray,
				t_cap_data *cap_data)
{
	t_vec3	hit_data[3];
	t_vec3	hit_pos;

	hit_pos = vec3_add(ray.orig, vec3_scale(ray.dir, cap_data->t));
	if (vec3_len(vec3_sub(hit_pos, cap_data->center)) <= cap_data->radius + EPSILON * 10)
	{
		hit_data[0].x = cap_data->t;
		hit_data[1] = hit_pos;
		hit_data[2] = cap_data->normal;
		fill_record_cap(hit, obj, ray, hit_data);
	}
}

static void	check_single_cap(t_hit_record *hit, t_obj *obj, t_ray ray,
				t_cap_params *params)
{
	t_cap_data	cap_data;

	cap_data.center = get_cap_center(obj, params->axis, params->height, params->is_top);
	cap_data.t = get_cap_t(cap_data.center, ray, params->axis);
	if (cap_data.t > EPSILON && (hit->t < 0 || cap_data.t < hit->t))
	{
		cap_data.radius = params->radius;
		cap_data.normal = params->is_top ? params->axis : vec3_scale(params->axis, -1.0);
		process_cap_hit(hit, obj, ray, &cap_data);
	}
}

static void	check_cap_hit(t_hit_record *hit, t_obj *obj, t_ray ray,
				const t_vec3 axis, const double params[2])
{
	t_cap_params	cap_params;

	cap_params.axis = axis;
	cap_params.radius = params[0];
	cap_params.height = params[1];
	
	cap_params.is_top = 0;
	check_single_cap(hit, obj, ray, &cap_params);
	
	cap_params.is_top = 1;
	check_single_cap(hit, obj, ray, &cap_params);
}

/* ───────────────────────── main hit ───────────────────────── */

t_hit_record	cylinder_hit(t_obj *obj, t_ray ray, t_app *app)
{
	t_hit_record	hit;
	t_vec3			axis;
	double			params[2];

	(void)app;
	hit.t = -1.0;
	axis = vec3_normalize(obj->u.cy.axis);
	params[0] = obj->u.cy.radius;
	params[1] = obj->u.cy.height;
	hit = check_side_hit(obj, ray, axis, params);
	check_cap_hit(&hit, obj, ray, axis, params);
	return (hit);
}
