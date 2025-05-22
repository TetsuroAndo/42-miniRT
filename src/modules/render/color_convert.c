/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:00:49 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/22 19:48:49 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"

t_rgbd	trgb_to_rgbd(int c)
{
	return ((t_rgbd){.r = ((c >> 16) & 0xFF) / 255.0,
		.g = ((c >> 8) & 0xFF) / 255.0,
		.b = (c & 0xFF) / 255.0});
}

int	rgbd_to_trgb(t_rgbd v)
{
	return (create_trgb(
			0,
			(int)(fmin(v.r, 1.0) * 255.0 + 0.5),
		(int)(fmin(v.g, 1.0) * 255.0 + 0.5),
			(int)(fmin(v.b, 1.0) * 255.0 + 0.5)));
}

t_rgbd	rgbd_add(t_rgbd a, t_rgbd b)
{
	return ((t_rgbd){a.r + b.r, a.g + b.g, a.b + b.b});
}

t_rgbd	rgbd_scale(t_rgbd a, double s)
{
	return ((t_rgbd){a.r * s, a.g * s, a.b * s});
}

int	create_trgb(int t, int r, int g, int b)
{
	if (255 < r)
		r = 255;
	if (255 < g)
		g = 255;
	if (255 < b)
		b = 255;
	return (t << 24 | r << 16 | g << 8 | b);
}
