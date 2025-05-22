/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:28:38 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/22 17:52:02 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"
#include "mod_thread.h"
#include "mod_accel.h"

t_rgbd trgb_to_rgbd(int c)
{
    return (t_rgbd){
        .r = ((c >> 16) & 0xFF) / 255.0,
        .g = ((c >>  8) & 0xFF) / 255.0,
        .b = ( c        & 0xFF) / 255.0};
}
int rgbd_to_trgb(t_rgbd v)
{
    return create_trgb(0,
        (int)(fmin(v.r,1.0)*255.0+0.5),
        (int)(fmin(v.g,1.0)*255.0+0.5),
        (int)(fmin(v.b,1.0)*255.0+0.5));
}
t_rgbd rgbd_add(t_rgbd a,t_rgbd b)
{
    return (t_rgbd){a.r+b.r,a.g+b.g,a.b+b.b};
}
t_rgbd rgbd_scale(t_rgbd a,double s)
{
    return (t_rgbd){a.r*s,a.g*s,a.b*s};
}

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

/* Implementation of init_cam_basis from get_ray_direction.c */
static t_cam_basis	init_cam_basis(t_camera *cam)
{
	t_cam_basis		basis;
	double			aspect;
	double			theta;
	t_vec3			world_up;
	double			dot_product;

	// デフォルトのworld_upベクトル
	world_up = vec3_new(0, 1, 0);
	basis.forward = vec3_normalize(cam->dir);
	// カメラの方向とworld_upが平行に近いかチェック
	dot_product = fabs(vec3_dot(basis.forward, world_up));
	if (dot_product > 0.9)
	{
		// 平行に近い場合は別の軸を使用
		world_up = vec3_new(0, 0, 1);
		// それでも平行なら最後の選択肢
		if (fabs(vec3_dot(basis.forward, world_up)) > 0.9)
			world_up = vec3_new(1, 0, 0);
	}

	basis.right = vec3_normalize(vec3_cross(basis.forward, world_up));
	basis.up = vec3_cross(basis.right, basis.forward);
	aspect = (double)WIDTH / (double)HEIGHT;
	theta = cam->fov * M_PI / 180.0;
	basis.half_h = tan(theta / 2.0);
	basis.half_w = aspect * basis.half_h;
	return (basis);
}

t_vec3 get_ray_dir_sub(t_camera *cam, double x, double y)
{
	/* get_ray_direction と同じ内容だが x,y が double */
	double u, v;
	t_cam_basis b = init_cam_basis(cam);
	u = (x + 0.5) / (double)WIDTH;
	v = (y + 0.5) / (double)HEIGHT;
	u = (2.0 * u - 1.0) * b.half_w;
	v = (1.0 - 2.0 * v) * b.half_h;
	return (vec3_normalize(vec3_add(b.forward,
				vec3_add(vec3_scale(b.right, u),
						 vec3_scale(b.up,    v)))));
}

/* 既存の calculate_light_color を "ローカル色" として double 版で呼び出す */
static t_rgbd shade_local(t_hit_record *hit, t_app *app)
{
	int trgb = calculate_light_color(hit, app);
	return trgb_to_rgbd(trgb);
}

t_rgbd trace_ray(t_ray ray, t_app *app, int depth)
{
	if (depth > MAX_DEPTH)
		return (t_rgbd){0.078,0.078,0.078};          /* 暗い背景 */

	t_hit_record h = intersect_ray(ray, app, INFINITY);
	if (h.t <= 0.0 || !h.obj)
		return (t_rgbd){0.078,0.078,0.078};          /* 背景 */

	/* 1) まず直接照明 */
	t_rgbd local = shade_local(&h, app);

	/* 2) 鏡面反射レイ */
	t_rgbd refl_col = {0,0,0};
	if (h.obj->reflect > 0.0)
	{
		t_vec3 R = vec3_sub(ray.dir,
					 vec3_scale(h.normal, 2.0*vec3_dot(ray.dir,h.normal)));
		t_ray  refl_ray = {
			.orig = vec3_add(h.pos, vec3_scale(h.normal, SHADOW_BIAS)),
			.dir  = vec3_normalize(R)};
		refl_col = trace_ray(refl_ray, app, depth+1);
	}
	return rgbd_add(
			rgbd_scale(local, 1.0 - h.obj->reflect),
			rgbd_scale(refl_col, h.obj->reflect));
}

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
		const double atten = l->bright * 20 / (dist * dist + 1.0);
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

	// /* ---------- 2. HDR / トーンマッピング ---------- */
	const double max_comp = fmax(sum_r, fmax(sum_g, sum_b));
	const double hdr_scale = 1.0 / (1.0 + max_comp);   /* Reinhard 1/(1+x) */
	sum_r *= hdr_scale;
	sum_g *= hdr_scale;
	sum_b *= hdr_scale;

	// /* ---------- 3. ガンマ 2.2 補正 ---------- */
	// sum_r = pow(sum_r, 1.0 / 2.2);
	// sum_g = pow(sum_g, 1.0 / 2.2);
	// sum_b = pow(sum_b, 1.0 / 2.2);

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
	int				color_value;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			/* ---- SSAA ×4 ---- */
			const double ofs[4][2] = {
				{0.25,0.25},{0.75,0.25},{0.25,0.75},{0.75,0.75}};
			t_rgbd sum = {0,0,0};
			for (int s=0;s<4;++s)
			{
				t_ray rr = {
					.orig = app->scene->cam.pos,
					.dir  = get_ray_dir_sub(&app->scene->cam,
										j+ofs[s][0], i+ofs[s][1])};
				sum = rgbd_add(sum, trace_ray(rr, app, 0));
			}
			sum = rgbd_scale(sum, 0.25);             /* 平均 */
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
	/* --- タイル + スレッド --- */
	const int cpu = sysconf(_SC_NPROCESSORS_ONLN);
	t_renderq *q  = make_tiles(app, 16);  /* 32px × 32px タイル */
	app->renderq  = q;
	spawn_workers(app, q, cpu - 1);       /* ← ここで全タイル完了 & join 済み */
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
