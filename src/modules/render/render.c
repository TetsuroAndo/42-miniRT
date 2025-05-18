/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:28:38 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/18 21:21:24 by tomsato          ###   ########.fr       */
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
	double	diff;
	double	distance;
	double	attenuation;
	double	diffuse_intensity;

	// アンビエント光
	ambient.r = (int)(hit->color.r * app->scene->amb.ratio
			* app->scene->amb.color.r / 255);
	ambient.g = (int)(hit->color.g * app->scene->amb.ratio
			* app->scene->amb.color.g / 255);
	ambient.b = (int)(hit->color.b * app->scene->amb.ratio
			* app->scene->amb.color.b / 255);

	// 拡散光のための計算
	light_dir = vec3_sub(lights->pos, hit->pos);
	distance = vec3_len(light_dir);
	light_dir = vec3_normalize(light_dir);
	diff = fmax(vec3_dot(hit->normal, light_dir), 0.0);
	attenuation = lights->bright / (distance * distance + 1);
	diffuse_intensity = diff * attenuation;

	// デバッグ出力
	printf("---- Light Debug ----\n");
	printf("Hit Pos: (%f, %f, %f)\n", hit->pos.x, hit->pos.y, hit->pos.z);
	printf("Normal: (%f, %f, %f)\n", hit->normal.x, hit->normal.y, hit->normal.z);
	printf("Light Pos: (%f, %f, %f)\n", lights->pos.x, lights->pos.y, lights->pos.z);
	printf("Distance: %f\n", distance);
	printf("Dot(N,L): %f\n", diff);
	printf("Attenuation: %f\n", attenuation);
	printf("Diffuse Intensity: %f\n", diffuse_intensity);
	printf("Ambient: (%d, %d, %d)\n", ambient.r, ambient.g, ambient.b);

	result.r = fmin(ambient.r + hit->color.r * diffuse_intensity, 255);
	result.g = fmin(ambient.g + hit->color.g * diffuse_intensity, 255);
	result.b = fmin(ambient.b + hit->color.b * diffuse_intensity, 255);

	printf("Final color: (%d, %d, %d)\n", result.r, result.g, result.b);
	printf("---------------------\n");

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
	if (min.t == INFINITY)
		min.t = 0;
	return (min);
}

void	render(t_img *img, t_app *app)
{
	int				i;
	int				j;
	t_ray			ray;
	t_hit_record	hit;
	int				color_value;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			ray.orig = app->scene->cam.pos;
			ray.dir = get_ray_direction(&app->scene->cam, i, j);
			hit = intersect_ray(ray, app);
			if (hit.t > EPSILON)
			{
				if (hit.obj != NULL)
				{
					color_value = create_trgb(0, hit.color.r, hit.color.g, hit.color.b);
				}
				else
				{
					color_value = create_trgb(0, 255, 0, 255);
				}
			}
			else
			{
				color_value = create_trgb(0, 20, 20, 20);
			}
			my_mlx_pixel_put(img, j, i, color_value);
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
