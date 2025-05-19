/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cylinder.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: teando <teando@student.42tokyo.jp>		 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/15 17:51:37 by tomsato		   #+#	#+#			 */
/*   Updated: 2025/05/20 05:04:40 by teando		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "mod_hit.h"

/*
**  Helper to solve quadratic a·t^2 + b·t + c = 0 and return the smallest
**  positive root that is > EPSILON, or -1.0 if none exists.
*/
static double  solve_quadratic(double a, double b, double c)
{
	double disc = b * b - 4.0 * a * c;
	if (disc < 0.0)
		return (-1.0);
	double sqrt_d = sqrt(disc);
	double t1 = (-b - sqrt_d) / (2.0 * a);
	double t2 = (-b + sqrt_d) / (2.0 * a);
	if (t1 > EPSILON)
		return (t1);
	if (t2 > EPSILON)
		return (t2);
	return (-1.0);
}

static void fill_record_side(t_hit_record *rec, t_obj *obj, t_ray ray, double t,
							  t_vec3 hit_pos, t_vec3 axis)
{
	rec->t   = t;
	rec->pos = hit_pos;
	// radial normal
	t_vec3 center_to_hit = vec3_sub(hit_pos, obj->u.cy.center);
	double proj = vec3_dot(center_to_hit, axis);
	t_vec3 radial = vec3_sub(center_to_hit, vec3_scale(axis, proj));
	rec->normal = vec3_normalize(radial);
	if (vec3_dot(rec->normal, ray.dir) > 0)
		rec->normal = vec3_scale(rec->normal, -1.0);
	rec->color  = obj->u.cy.color;
	rec->obj	= obj;
}

static void fill_record_cap(t_hit_record *rec, t_obj *obj, t_ray ray, double t,
							 t_vec3 hit_pos, t_vec3 axis, int top)
{
	(void)top;
	rec->t   = t;
	rec->pos = hit_pos;
	rec->normal = axis;			// +axis for top cap, -axis for bottom
	if (!top)
		rec->normal = vec3_scale(axis, -1.0);
	if (vec3_dot(rec->normal, ray.dir) > 0)
		rec->normal = vec3_scale(rec->normal, -1.0);
	rec->color = obj->u.cy.color;
	rec->obj   = obj;
}



t_hit_record	cylinder_hit(t_obj *obj, t_ray ray, t_app *app)
{
	(void)app;
	t_hit_record	hit;
	hit.t = -1.0;
	const t_vec3 axis = vec3_normalize(obj->u.cy.axis);
	const double r	= obj->u.cy.radius;
	const double h	= obj->u.cy.height;

	/* --- side intersection ------------------------------------------------*/
	t_vec3  oc   = vec3_sub(ray.orig, obj->u.cy.center);
	double  d_dot_a = vec3_dot(ray.dir, axis);
	double  oc_dot_a = vec3_dot(oc, axis);

	t_vec3  d_perp = vec3_sub(ray.dir, vec3_scale(axis, d_dot_a));
	t_vec3  oc_perp = vec3_sub(oc, vec3_scale(axis, oc_dot_a));
	double  a = vec3_dot(d_perp, d_perp);
	double  b = 2.0 * vec3_dot(d_perp, oc_perp);
	double  c = vec3_dot(oc_perp, oc_perp) - r * r;

	double  t_side = solve_quadratic(a, b, c);
	if (t_side > 0)
	{
		t_vec3 p = vec3_add(ray.orig, vec3_scale(ray.dir, t_side));
		double  m = vec3_dot(vec3_sub(p, obj->u.cy.center), axis);
		if (m >= -h / 2.0 && m <= h / 2.0)
			fill_record_side(&hit, obj, ray, t_side, p, axis);
	}
	/* --- caps -------------------------------------------------------------*/
	double ts[2];
	double denom = vec3_dot(ray.dir, axis);
	if (fabs(denom) > EPSILON)
	{
		// bottom cap  (center - axis*h/2)
		t_vec3 pc = vec3_sub(obj->u.cy.center, vec3_scale(axis, h / 2.0));
		ts[0] = vec3_dot(vec3_sub(pc, ray.orig), axis) / denom;
		// top cap (center + axis*h/2)
		t_vec3 pt = vec3_add(obj->u.cy.center, vec3_scale(axis, h / 2.0));
		ts[1] = vec3_dot(vec3_sub(pt, ray.orig), axis) / denom;

		for (int i = 0; i < 2; ++i)
		{
			double t = ts[i];
			if (t > EPSILON && (hit.t < 0 || t < hit.t))
			{
				t_vec3 ph = vec3_add(ray.orig, vec3_scale(ray.dir, t));
				t_vec3 center_cap = (i == 0) ? pc : pt;
				if (vec3_len(vec3_sub(ph, center_cap)) <= r + EPSILON)
				{
					fill_record_cap(&hit, obj, ray, t, ph, axis, i); // i==1 top
				}
			}
		}
	}

	return (hit);
}
