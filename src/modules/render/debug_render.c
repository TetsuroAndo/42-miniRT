/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 05:54:50 by teando            #+#    #+#             */
/*   Updated: 2025/05/20 06:09:08 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"

void	temp(t_img *img)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	j = 0;
	color = create_trgb(0, 0, 0, 0);
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			color = create_trgb(0, 0, 0, 0);
			if ((i % 50 > 25 && j % 50 < 25) || (i % 50 < 25 && j % 50 > 25))
				color = create_trgb(0, 255, 255, 255);
			my_mlx_pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}
