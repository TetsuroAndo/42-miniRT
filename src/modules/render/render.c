/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:28:38 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/08 21:15:24 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->px + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static void	temp(t_img *img)
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

void	render(t_img *img, t_app *app)
{
	int	i;
	int	j;
	t_ray	ray;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < HEIGHT)
		{
			//レイの方向を取得
			ray.orig = app->scene->cam.pos;
			ray.dir = get_ray_direction(app->scene->cam, i, j);
			//交差判定をする
			//ライトを参照して、色を取得
			//my_mlx_pixel_putする
			j++;
		}
		i++;
	}
}

void	draw(t_app *app)
{
	t_img *img;

	app->mlx = mlx_init();
	if (!app->mlx)
		exit_app(app, 1);
	app->win = mlx_new_window(app->mlx, WIDTH, HEIGHT, "miniRT");
	if (!app->win)
		exit_app(app, 1);
	img = app->img;
	img->width = WIDTH;
	img->height = HEIGHT;
	img->ptr = mlx_new_image(app->mlx, img->width, img->height);
	if (!img->ptr)
		exit_app(app, 1);
	img->px = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len,
			&img->endian);
	temp(img);
	mlx_put_image_to_window(app->mlx, app->win, img->ptr, 0, 0);
}