/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:33:11 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/08 20:35:23 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_vec.h"

t_vec3	vec3_new(double x, double y, double z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}
