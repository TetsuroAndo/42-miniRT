/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:33:11 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/10 19:12:18 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vec.h"
#include <stdio.h>

t_vec3	vec3_new(double x, double y, double z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_vec3	vec3_scale(t_vec3 v, double s)
{
	t_vec3	result;

	result.x = v.x * s;
	result.y = v.y * s;
	result.z = v.z * s;
	return (result);
}

void	vec3_print(t_vec3 v)
{
	printf("x:%f, y:%f, z%f\n", v.x, v.y, v.z);
}

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}