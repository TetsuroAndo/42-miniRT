/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:15:51 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 10:15:58 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_accel.h"
#include "rt_vec.h"

t_aabb aabb_merge(t_aabb a, t_aabb b)
{
	t_aabb result;
	result.min = (t_vec3){fmin(a.min.x,b.min.x), fmin(a.min.y,b.min.y), fmin(a.min.z,b.min.z)};
	result.max = (t_vec3){fmax(a.max.x,b.max.x), fmax(a.max.y,b.max.y), fmax(a.max.z,b.max.z)};
	return result;
}

int aabb_hit(t_aabb box, t_ray r, double t_max)
{
	for (int i = 0; i < 3; ++i)
	{
		const double invD = 1.0 / ((double *)&r.dir)[i];
		double t0 = (((double *)&box.min)[i] - ((double *)&r.orig)[i]) * invD;
		double t1 = (((double *)&box.max)[i] - ((double *)&r.orig)[i]) * invD;
		if (invD < 0.0)
		{
			double tmp = t0;
			t0 = t1;
			t1 = tmp;
		}
		if (t1 < 0.0 || t0 > t_max)
			return (0);
		t_max = fmin(t_max, t1);
	}
	return (1);
}

/* オブジェクトごとの bbox （無限平面は巨大 box で妥協） */
t_aabb obj_bbox(t_obj *o)
{
	t_aabb result;
	switch (o->type)
	{
	case OBJ_SPHERE:
	{
		t_vec3 radius_vec = {o->u.sp.radius, o->u.sp.radius, o->u.sp.radius};
		result.min = vec3_sub(o->u.sp.center, radius_vec);
		result.max = vec3_add(o->u.sp.center, radius_vec);
		return result;
	}
	case OBJ_CYLINDER:
	{
		t_vec3 size = {o->u.cy.radius, o->u.cy.height*0.5, o->u.cy.radius};
		result.min = vec3_sub(o->u.cy.center, size);
		result.max = vec3_add(o->u.cy.center, size);
		return result;
	}
	default:
		result.min = (t_vec3){-INFINITY, -INFINITY, -INFINITY};
		result.max = (t_vec3){INFINITY, INFINITY, INFINITY};
		return result;
	}
}
