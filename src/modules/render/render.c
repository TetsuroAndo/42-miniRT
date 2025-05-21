/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:28:38 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/21 10:27:43 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"
#include "mod_thread.h"
#include "mod_accel.h"

static inline unsigned char	clamp255(int x)
{
	if (x > 255)
		return (255);
	return ((unsigned char)x);
}

/* 反射ベクトル (未使用ならコメントアウト可) */
// static inline t_vec3 reflect_vec(t_vec3 v, t_vec3 n)
// {
// 	return vec3_sub(v, vec3_scale(n, 2.0 * vec3_dot(v, n)));
// }

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->px + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | clamp255(r) << 16 | clamp255(g) << 8 | clamp255(b));
}

t_hit_record	intersect_ray(t_ray ray, t_app *app, double t_max);

int	is_shadow(t_hit_record *hit, t_lights *light, t_app *app)
{
	// 影判定: ヒット点から光源へのレイを飛ばし、途中で遮るものがあるか
	t_vec3 dir = vec3_sub(light->pos, hit->pos);
	double t_max = vec3_len(dir);
	dir = vec3_normalize(dir);

	// 数値誤差を避けるため、ヒット点を法線方向に一定距離だけ移動
	t_ray shadow_ray = {
		.orig = vec3_add(hit->pos, vec3_scale(hit->normal, SHADOW_BIAS)),
		.dir = dir
	};

	// 交差判定（t_maxを渡して光源手前の遮蔽のみ検出）
	t_hit_record s = intersect_ray(shadow_ray, app, t_max);

	// 何かにヒットしたら影の中
	return (s.t > 0.0);
}

int	calculate_light_color(t_hit_record *hit, t_app *app)
{
	/* ---------- 0. 準備 ---------- */
	const t_color amb_col  = app->scene->amb.color;
	const double  amb_ratio = app->scene->amb.ratio;

	/* 色成分は double で計算 (0〜∞) */
	double sum_r = (hit->color.r / 255.0) * (amb_col.r / 255.0) * amb_ratio;
	double sum_g = (hit->color.g / 255.0) * (amb_col.g / 255.0) * amb_ratio;
	double sum_b = (hit->color.b / 255.0) * (amb_col.b / 255.0) * amb_ratio;

	const t_vec3 view_dir = vec3_normalize(
			vec3_sub(app->scene->cam.pos, hit->pos));   /* V ベクトル */

	/* ---------- 1. 各ライトをループ ---------- */
	for (t_lights *l = app->scene->lights; l; l = l->next)
	{
		if (is_shadow(hit, l, app))
			continue;   /* 影ならスキップ */

		/* ライト → 点まで */
		t_vec3 light_dir = vec3_sub(l->pos, hit->pos);
		const double dist = vec3_len(light_dir);
		light_dir = vec3_normalize(light_dir);

		/* 拡散 (Lambert) */
		const double diff  = fmax(vec3_dot(hit->normal, light_dir), 0.0);
		const double atten = l->bright / (dist * dist + 1.0);
		const double kd = diff * atten;

		/* スペキュラ (Blinn–Phong) */
		const t_vec3 half_dir = vec3_normalize(vec3_add(light_dir, view_dir));
		const double spec_dot = fmax(vec3_dot(hit->normal, half_dir), 0.0);
		const double ks = pow(spec_dot, hit->obj->shininess) * atten;

		/* ライト色正規化 */
		const double lr = l->color.r / 255.0;
		const double lg = l->color.g / 255.0;
		const double lb = l->color.b / 255.0;

		/* 拡散寄与 */
		sum_r += (hit->color.r / 255.0) * lr * kd;
		sum_g += (hit->color.g / 255.0) * lg * kd;
		sum_b += (hit->color.b / 255.0) * lb * kd;

		/* スペキュラ寄与 */
		sum_r += (hit->obj->spec.r / 255.0) * lr * ks;
		sum_g += (hit->obj->spec.g / 255.0) * lg * ks;
		sum_b += (hit->obj->spec.b / 255.0) * lb * ks;
	}

	/* ---------- 2. HDR / トーンマッピング ---------- */
	const double max_comp = fmax(sum_r, fmax(sum_g, sum_b));
	const double hdr_scale = 1.0 / (1.0 + max_comp);   /* Reinhard 1/(1+x) */
	sum_r *= hdr_scale;
	sum_g *= hdr_scale;
	sum_b *= hdr_scale;

	/* ---------- 3. ガンマ 2.2 補正 ---------- */
	sum_r = pow(sum_r, 1.0 / 2.2);
	sum_g = pow(sum_g, 1.0 / 2.2);
	sum_b = pow(sum_b, 1.0 / 2.2);

	/* ---------- 4. 0-255 へ戻して TRGB ---------- */
	return create_trgb(0,
			(int)(sum_r * 255.0 + 0.5),
			(int)(sum_g * 255.0 + 0.5),
			(int)(sum_b * 255.0 + 0.5));
}


t_hit_record	intersect_ray(t_ray ray, t_app *app, double t_max)
{
	t_hit_record rec = {.t = INFINITY, .obj = NULL};
	if (!bvh_hit(app->bvh, ray, t_max, &rec))
		rec.t = 0.0;
	return rec;
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
			hit = intersect_ray(ray, app, INFINITY);
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
	/* --- タイル + スレッド --- */
	const int cpu = sysconf(_SC_NPROCESSORS_ONLN);
	t_renderq *q  = make_tiles(app, 16);  /* 32px × 32px タイル */
	app->renderq  = q;
	spawn_workers(app, q, cpu - 1);       /* メイン含めて cpu スレッド */
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
