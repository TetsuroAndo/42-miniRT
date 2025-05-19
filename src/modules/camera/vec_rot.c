/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 05:30:00 by teando            #+#    #+#             */
/*   Updated: 2025/05/20 06:02:58 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_cam.h"
#include <math.h>

t_vec3	vec3_rotate(t_vec3 v, t_vec3 axis, double angle)
{
	double	c;
	double	s;
	t_vec3	term1;
	t_vec3	term2;
	t_vec3	term3;

	axis = vec3_normalize(axis);
	c = cos(angle);
	s = sin(angle);
	term1 = vec3_scale(v, c);
	term2 = vec3_scale(vec3_cross(axis, v), s);
	term3 = vec3_scale(axis, vec3_dot(axis, v) * (1 - c));
	return (vec3_add(vec3_add(term1, term2), term3));
}
