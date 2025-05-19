/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:28:38 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/20 07:35:34 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"

/* Forward declarations */
t_hit_record	intersect_ray(t_ray ray, t_app *app);

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

int	is_shadow(t_hit_record *hit, t_lights *light, t_app *app)
{
	// 影判定: ヒット点から光源へのレイを飛ばし、途中で遮るものがあるか
	t_vec3 dir_to_light = vec3_sub(light->pos, hit->pos);
	double dist_to_light = vec3_len(dir_to_light);
	dir_to_light = vec3_normalize(dir_to_light);

	// オブジェクトの半径に基づいて適切なオフセットを計算
	double radius = 0.0;
	if (hit->obj)
	{
		if (hit->obj->type == OBJ_SPHERE)
			radius = hit->obj->u.sp.radius;
		else if (hit->obj->type == OBJ_CYLINDER)
			radius = hit->obj->u.cy.radius;
	}
	// 数値誤差を避けるため、ヒット点を適切な距離だけ法線方向に移動
	// 小さいオブジェクトでも確実に自己交差を避けるため、半径に基づいて調整
	double offset = fmax(radius * 0.001, EPSILON);
	t_ray shadow_ray;
	shadow_ray.orig = vec3_add(hit->pos, vec3_scale(dir_to_light, offset));
	shadow_ray.dir = dir_to_light;

	// 交差判定
	t_hit_record shadow_hit = intersect_ray(shadow_ray, app);

	// 光源までの距離より手前で何かにヒットしたら影の中
	return (shadow_hit.t > 0 && shadow_hit.t < dist_to_light);
}

int	calculate_light_color(t_hit_record *hit, t_app *app)
{
	/* ---- ambient -------------------------------------------------------- */
	t_color sum;
	sum.r = (int)(hit->color.r * app->scene->amb.ratio * app->scene->amb.color.r / 255.0);
	sum.g = (int)(hit->color.g * app->scene->amb.ratio * app->scene->amb.color.g / 255.0);
	sum.b = (int)(hit->color.b * app->scene->amb.ratio * app->scene->amb.color.b / 255.0);

	/* ---- diffuse for every spot ---------------------------------------- */
	for (t_lights *l = app->scene->lights; l; l = l->next)
	{
		if (is_shadow(hit, l, app))
			continue; /* スキップ: この光源からの光は影になっている */

		t_vec3 light_dir = vec3_sub(l->pos, hit->pos);
		double dist      = vec3_len(light_dir);
		light_dir        = vec3_normalize(light_dir);

		double diff  = fmax(vec3_dot(hit->normal, light_dir), 0.0);
		double atten = l->bright / (dist * dist + 1.0);
		double intens = diff * atten;

		sum.r += hit->color.r * intens * (l->color.r / 255.0);
		sum.g += hit->color.g * intens * (l->color.g / 255.0);
		sum.b += hit->color.b * intens * (l->color.b / 255.0);
	}

	return create_trgb(0, CLAMP255(sum.r), CLAMP255(sum.g), CLAMP255(sum.b));
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
			ray.dir = get_ray_direction(&app->scene->cam, j, i);
			hit = intersect_ray(ray, app);
			if (hit.t > 0 && hit.obj)
				color_value = calculate_light_color(&hit, app);
			else
				color_value = create_trgb(0, 20, 20, 20);
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
	if (DEBUG_MODE & DEBUG_RENDER)
		temp(img);
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
