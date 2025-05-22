/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_side.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:46:13 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 19:11:47 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_hit.h"

void					cy_set_record(t_hit_record *rec, t_obj *obj, t_vec3 pos,
							double t);
void					cy_apply_face_orientation(t_hit_record *rec, t_ray ray);

static inline double	cy_get_valid_t(double a, double b, double disc)
{
	double	sqrt_d;
	double	t1;
	double	t2;

	sqrt_d = sqrt(disc);
	t1 = (-b - sqrt_d) / (2.0 * a);
	if (t1 > EPSILON)
		return (t1);
	t2 = (-b + sqrt_d) / (2.0 * a);
	if (t2 > EPSILON)
		return (t2);
	return (-1.0);
}

static inline double	cy_solve_quadratic(double a, double b, double c)
{
	double	disc;

	disc = b * b - 4.0 * a * c;
	if (disc < 0.0)
		return (-1.0);
	return (cy_get_valid_t(a, b, disc));
}

static inline double	cy_side_t(t_ray ray, t_vec3 oc, t_vec3 axis, double r)
{
	t_vec3	d_perp;
	t_vec3	oc_perp;
	double	a;
	double	b;
	double	c;

	d_perp = vec3_sub(ray.dir, vec3_scale(axis, vec3_dot(ray.dir, axis)));
	a = vec3_dot(d_perp, d_perp);
	if (fabs(a) < EPSILON)
		return (-1.0);
	oc_perp = vec3_sub(oc, vec3_scale(axis, vec3_dot(oc, axis)));
	b = 2.0 * vec3_dot(d_perp, oc_perp);
	c = vec3_dot(oc_perp, oc_perp) - r * r;
	return (cy_solve_quadratic(a, b, c));
}

static inline t_vec3	cy_side_normal(t_vec3 hit, t_vec3 ctr, t_vec3 axis)
{
	t_vec3	ch;
	t_vec3	radial;
	double	proj;

	ch = vec3_sub(hit, ctr);
	proj = vec3_dot(ch, axis);
	radial = vec3_sub(ch, vec3_scale(axis, proj));
	return (vec3_normalize(radial));
}

void	cy_check_side(t_hit_record *hit, t_obj *obj, t_ray ray, t_vec3 axis)
{
	t_vec3	oc;
	double	t;
	double	m;
	t_vec3	pos;

	oc = vec3_sub(ray.orig, obj->u.cy.center);
	t = cy_side_t(ray, oc, axis, obj->u.cy.radius);
	if (t <= EPSILON || (hit->t > 0 && t >= hit->t))
		return ;
	pos = vec3_add(ray.orig, vec3_scale(ray.dir, t));
	m = vec3_dot(vec3_sub(pos, obj->u.cy.center), axis);
	if (fabs(m) > obj->u.cy.height * 0.5 + EPSILON)
		return ;
	cy_set_record(hit, obj, pos, t);
	hit->normal = cy_side_normal(pos, obj->u.cy.center, axis);
	cy_apply_face_orientation(hit, ray);
}
