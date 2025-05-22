/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:42:22 by teando            #+#    #+#             */
/*   Updated: 2025/05/15 22:05:07 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

int	parse_vec3(char **s, t_vec3 *out)
{
	skip_ws(s);
	if (!parse_f64(s, &out->x, -INFINITY, INFINITY))
		return (0);
	if (!expect_char(s, ','))
		return (0);
	if (!parse_f64(s, &out->y, -INFINITY, INFINITY))
		return (0);
	if (!expect_char(s, ','))
		return (0);
	if (!parse_f64(s, &out->z, -INFINITY, INFINITY))
		return (0);
	return (1);
}

int	parse_normal_vec3(char **s, t_vec3 *out)
{
	double	len;

	if (!parse_vec3(s, out))
		return (0);
	if (out->x < -1.0 || out->x > 1.0 || out->y < -1.0 || out->y > 1.0
		|| out->z < -1.0 || out->z > 1.0)
		return (0);
	if (out->x == 0.0 && out->y == 0.0 && out->z == 0.0)
		return (0);
	len = sqrt(out->x * out->x + out->y * out->y + out->z * out->z);
	if (len < 1e-6)
		return (0);
	out->x /= len;
	out->y /= len;
	out->z /= len;
	return (1);
}
