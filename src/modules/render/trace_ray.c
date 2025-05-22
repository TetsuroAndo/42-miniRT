/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:43:49 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/22 19:52:16 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"

/* 既存の calculate_light_color を "ローカル色" として double 版で呼び出す */
t_rgbd	shade_local(t_hit_record *hit, t_app *app)
{
	int	trgb;

	trgb = calculate_light_color(hit, app);
	return (trgb_to_rgbd(trgb));
}

t_rgbd	trace_ray(t_ray ray, t_app *app, int depth)
{
	t_vec3			r;
	t_ray			refl_ray;
	t_rgbd			refl_col;
	t_hit_record	h;
	t_rgbd			local;

	h = intersect_ray(ray, app, INFINITY);
	if (h.t <= 0.0 || !h.obj)
		return ((t_rgbd){0.078, 0.078, 0.078});
	local = shade_local(&h, app);
	refl_col = (t_rgbd){0, 0, 0};
	if (h.obj->reflect > 0.0 && depth < MAX_DEPTH)
	{
		r = vec3_sub(ray.dir, vec3_scale(h.normal, 2.0 * vec3_dot(ray.dir,
						h.normal)));
		refl_ray = (t_ray){.orig = vec3_add(h.pos, vec3_scale(h.normal,
					SHADOW_BIAS)), .dir = vec3_normalize(r)};
		refl_col = trace_ray(refl_ray, app, depth + 1);
	}
	return (rgbd_add(rgbd_scale(local, 1.0 - h.obj->reflect),
			rgbd_scale(refl_col, h.obj->reflect)));
}

int	is_shadow(t_hit_record *hit, t_lights *light, t_app *app)
{
	const t_vec3		dir = vec3_normalize(vec3_sub(light->pos, hit->pos));
	const double		t_max = vec3_len(dir);
	const t_ray			shadow_ray = {.orig = vec3_add(hit->pos,
			vec3_scale(hit->normal, SHADOW_BIAS)), .dir = dir};
	const t_hit_record	s = intersect_ray(shadow_ray, app, t_max);

	return (s.t > 0.0);
}

/* --- ここをシンプルなリニア交差テストに置き換え --- */
t_hit_record	intersect_ray(t_ray ray, t_app *app, double t_max)
{
	t_hit_record	rec;
	t_hit_record	closest;
	t_obj			*o;

	closest = (t_hit_record){.t = t_max, .obj = NULL};
	o = app->scene->objs;
	while (o)
	{
		rec = o->hit(o, ray, app);
		if (rec.t > 0.0 && rec.t < closest.t)
			closest = rec;
		o = o->next;
	}
	if (!closest.obj)
		closest.t = 0.0;
	return (closest);
}
