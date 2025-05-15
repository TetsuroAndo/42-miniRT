/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:31:02 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/15 17:05:21 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vec.h"
#include <math.h>

t_vec3	vec3_new(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vec3	vec3_mul(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}

t_vec3	vec3_scale(t_vec3 v, double s)
{
	return ((t_vec3){v.x * s, v.y * s, v.z * s});
}
