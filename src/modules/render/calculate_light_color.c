/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_light_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:08:24 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/22 21:11:02 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"

static inline void	apply_diffuse(t_vec3 *sum, const t_hit_record *hit,
		const t_color *light_col, double kd)
{
	sum->x += (hit->color.r / 255.0) * (light_col->r / 255.0) * kd;
	sum->y += (hit->color.g / 255.0) * (light_col->g / 255.0) * kd;
	sum->z += (hit->color.b / 255.0) * (light_col->b / 255.0) * kd;
}

static inline void	apply_specular(t_vec3 *sum, const t_hit_record *hit,
		const t_color *light_col, double ks)
{
	sum->x += (hit->obj->spec.r / 255.0) * (light_col->r / 255.0) * ks;
	sum->y += (hit->obj->spec.g / 255.0) * (light_col->g / 255.0) * ks;
	sum->z += (hit->obj->spec.b / 255.0) * (light_col->b / 255.0) * ks;
}

static inline void	apply_light_contrib(t_vec3 *sum, const t_hit_record *hit,
		const t_lights *l, const t_vec3 view_dir)
{
	const t_vec3	light_dir = vec3_normalize(vec3_sub(l->pos, hit->pos));
	const double	dist = vec3_len(vec3_sub(l->pos, hit->pos));
	const double	atten = l->bright * 42 / (dist * dist + 1.0);
	double			kd;
	double			ks;

	kd = calc_kd(hit, light_dir, atten);
	ks = calc_ks(hit, light_dir, view_dir, atten);
	apply_diffuse(sum, hit, &l->color, kd);
	apply_specular(sum, hit, &l->color, ks);
}

static inline void	apply_tone_mapping(t_vec3 *color)
{
	const double	max_comp = fmax(color->x, fmax(color->y, color->z));
	const double	hdr_scale = 1.0 / (1.0 + max_comp);

	color->x *= hdr_scale;
	color->y *= hdr_scale;
	color->z *= hdr_scale;
}

int	calculate_light_color(t_hit_record *hit, t_app *app)
{
	const t_color	amb_col = app->scene->amb.color;
	const double	amb_ratio = app->scene->amb.ratio;
	t_vec3			sum;
	const t_vec3	view_dir = vec3_normalize(vec3_sub(app->scene->cam.pos,
				hit->pos));
	t_lights		*l;

	sum = vec3_new((hit->color.r / 255.0) * (amb_col.r / 255.0) * amb_ratio,
			(hit->color.g / 255.0) * (amb_col.g / 255.0) * amb_ratio,
			(hit->color.b / 255.0) * (amb_col.b / 255.0) * amb_ratio);
	l = app->scene->lights;
	while (l)
	{
		if (!is_shadow(hit, l, app))
			apply_light_contrib(&sum, hit, l, view_dir);
		l = l->next;
	}
	apply_tone_mapping(&sum);
	return (create_trgb(0, (int)(sum.x * 255.0 + 0.5), (int)(sum.y * 255.0
		+ 0.5), (int)(sum.z * 255.0 + 0.5)));
}
