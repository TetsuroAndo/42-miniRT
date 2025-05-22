/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_lights_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:19:28 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/22 20:20:30 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"

double	calc_kd(const t_hit_record *hit, t_vec3 light_dir, double atten)
{
	const double	diff = fmax(vec3_dot(hit->normal, light_dir), 0.0);

	return (diff * atten);
}

double	calc_ks(const t_hit_record *hit, t_vec3 light_dir, t_vec3 view_dir,
		double atten)
{
	t_vec3	half_dir;
	double	spec_dot;

	half_dir = vec3_normalize(vec3_add(light_dir, view_dir));
	spec_dot = fmax(vec3_dot(hit->normal, half_dir), 0.0);
	return (pow(spec_dot, hit->obj->shininess) * atten);
}
