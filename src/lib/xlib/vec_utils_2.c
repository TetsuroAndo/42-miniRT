/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:33:11 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/15 22:32:01 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vec.h"
#include <stdio.h>

void	vec3_print(t_vec3 v)
{
	printf("x:%f, y:%f, z%f\n", v.x, v.y, v.z);
}

double	vec3_len(t_vec3 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	double	len;

	len = vec3_len(v);
	if (len == 0.0)
		return (v);
	return ((t_vec3){v.x / len, v.y / len, v.z / len});
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

t_vec3	vec3_div(t_vec3 v, double t)
{
	return ((t_vec3){v.x / t, v.y / t, v.z / t});
}
