/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:28:38 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/22 20:01:29 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"

/* 反射ベクトル (未使用ならコメントアウト可) */
// static inline t_vec3 reflect_vec(t_vec3 v, t_vec3 n)
// {
// 	return (vec3_sub(v, vec3_scale(n, 2.0 * vec3_dot(v, n))));
// }

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->px + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render(t_img *img, t_app *app)
{
	int		i;
	int		j;
	int		color_value;
	t_ray	rr;
	t_rgbd	sum;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			rr = (t_ray){.orig = app->scene->cam.pos,
				.dir = get_ray_direction(&app->scene->cam, j, i)};
			sum = trace_ray(rr, app, 0);
			color_value = rgbd_to_trgb(sum);
			my_mlx_pixel_put(img, j, i, color_value);
			j++;
		}
		i++;
	}
}

void	init_render(t_app *app)
{
	t_img	*img;

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
	render(img, app);
	mlx_put_image_to_window(app->mlx, app->win, img->ptr, 0, 0);
}

int	redraw_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (app->dirty == 0)
		return (0);
	app->dirty = 0;
	render(app->img, app);
	mlx_put_image_to_window(app->mlx, app->win, app->img->ptr, 0, 0);
	return (0);
}
