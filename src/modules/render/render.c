/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:28:38 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/15 22:22:36 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"

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

int	is_shadow(t_hit_record *hit, t_app *app)
{
	(void)hit;
	(void)app;
	//影かどうかの判定
	return (0);
}

int	calculate_light_color(t_hit_record *hit, t_lights *lights, t_app *app)
{
	t_color	result;
	t_color	ambient;
	t_vec3	light_dir;
	double	distance;
	double	diffuse_intensity;

	ambient.r = (int)(hit->color.r * app->scene->amb.ratio
			* app->scene->amb.color.r / 255);
	ambient.g = (int)(hit->color.g * app->scene->amb.ratio
			* app->scene->amb.color.g / 255);
	ambient.b = (int)(hit->color.b * app->scene->amb.ratio
			* app->scene->amb.color.b / 255);
	light_dir = vec3_sub(lights->pos, hit->pos);
	distance = vec3_len(light_dir);
	diffuse_intensity = lights->bright / (distance * distance);
	diffuse_intensity = fmin(fmax(diffuse_intensity, 0.0), 1.0);
	result.r = fmin(ambient.r + (int)(hit->color.r * diffuse_intensity), 255);
	result.g = fmin(ambient.g + (int)(hit->color.g * diffuse_intensity), 255);
	result.b = fmin(ambient.b + (int)(hit->color.b * diffuse_intensity), 255);
	return (create_trgb(0, result.r, result.g, result.b));
}

t_hit_record	intersect_ray(t_ray ray, t_app *app)
{
	t_obj			*obj;
	t_hit_record	min;
	t_hit_record	tmp;

	min.t = INFINITY;
	obj = app->scene->objs;
	while (obj)
	{
		tmp = obj->hit(obj, ray, app);
		if (0 < tmp.t && tmp.t < min.t)
			min = tmp;
		obj = obj->next;
	}
	return (min);
}

void	render(t_img *img, t_app *app)
{
	int				i;
	int				j;
	t_ray			ray;
	t_hit_record	*hit;
	int				color;

	hit = (t_hit_record *)xcalloc(sizeof(t_hit_record), 1, app);
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			//レイの方向を取得
			ray.orig = app->scene->cam.pos;
			ray.dir = get_ray_direction(&app->scene->cam, i, j);
			//交差判定をする
			//ライトを参照して、色を取得
			hit->color.r = 255;
			hit->color.g = 0;
			hit->color.b = 0;
			// 仮の色を設定（後で実際のレイトレーシング結果に置き換える）
			color = create_trgb(0, 0, 0, 0);
			if (is_shadow(hit, app))
				color = create_trgb(0, 0, 0, 0);
			else
				color = calculate_light_color(hit, app->scene->lights, app);
			// color = create_trgb(0, i % 256, j % 256, (i + j) % 256);
			// 画像にピクセルを描画
			my_mlx_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw(t_app *app)
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
	temp(img);
	render(img, app);
	mlx_put_image_to_window(app->mlx, app->win, img->ptr, 0, 0);
}
