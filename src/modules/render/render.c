/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:28:38 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/08 13:17:49 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->px + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}


void	draw(t_app *app)
{
	void	*mlx;
	void	*win;
	t_img	*img;

	mlx = app->mlx;
	img = app->img;
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	img->width = WIDTH;
	img->height = HEIGHT;
	img->ptr = mlx_new_image(mlx, img->width, img->height);
	img->px = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_len, &img->endian);
	// ← ここに描画処理（my_mlx_pixel_putなど）を追加
	mlx_put_image_to_window(mlx, win, img->ptr, 0, 0);
}
