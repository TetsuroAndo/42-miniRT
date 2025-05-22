/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_render.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:20:32 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 18:27:08 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_RENDER_H
# define MOD_RENDER_H

# include "xlib.h"
# include <math.h>

typedef struct s_cam_basis
{
	t_vec3		forward;
	t_vec3		right;
	t_vec3		up;
	double		half_w;
	double		half_h;
}				t_cam_basis;

#define SHADOW_BIAS 1e-4
#define MAX_DEPTH   3   /* 再帰反射だけ残す */


/* 便利関数：TRGB ⇔ RGB ベクタ */
typedef struct s_rgbd
{
	double r, g, b;
}				t_rgbd;

t_rgbd			trgb_to_rgbd(int c);
int				rgbd_to_trgb(t_rgbd v);
t_rgbd			rgbd_add(t_rgbd a, t_rgbd b);
t_rgbd			rgbd_scale(t_rgbd a, double s);

void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
int				create_trgb(int t, int r, int g, int b);
t_vec3			get_ray_direction(t_camera *cam, int i, int j);
/* 中心 0.5,0.5 サンプリングは既存 get_ray_direction() を使う */

int				redraw_loop(void *param);
void			render(t_img *img, t_app *app);
void			init_render(t_app *app);

/* shadow and lighting */
int				is_shadow(t_hit_record *hit, t_lights *light, t_app *app);
int				calculate_light_color(t_hit_record *hit, t_app *app);

/* ray tracing */
t_rgbd			trace_ray(t_ray ray, t_app *app, int depth);

t_hit_record	intersect_ray(t_ray ray, t_app *app, double t_max);
int				calculate_light_color(t_hit_record *hit, t_app *app);

#endif