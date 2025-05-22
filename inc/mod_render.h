/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_render.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:20:32 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 23:41:33 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_RENDER_H
# define MOD_RENDER_H

# include "rt_scene.h"
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

# define SHADOW_BIAS 1e-4
# define MAX_DEPTH 3

typedef struct s_rgbd
{
	double		r;
	double		g;
	double		b;
}				t_rgbd;

t_rgbd			trgb_to_rgbd(int c);
int				rgbd_to_trgb(t_rgbd v);
t_rgbd			rgbd_add(t_rgbd a, t_rgbd b);
t_rgbd			rgbd_scale(t_rgbd a, double s);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
int				create_trgb(int t, int r, int g, int b);
t_vec3			get_ray_direction(t_camera *cam, int i, int j);
t_cam_basis		init_cam_basis(t_camera *cam);
t_rgbd			shade_local(t_hit_record *hit, t_app *app);
int				redraw_loop(void *param);
void			render(t_img *img, t_app *app);
void			init_render(t_app *app);
int				is_shadow(t_hit_record *hit, t_lights *light, t_app *app);
int				calculate_light_color(t_hit_record *hit, t_app *app);
t_rgbd			trace_ray(t_ray ray, t_app *app, int depth);

t_hit_record	intersect_ray(t_ray ray, t_app *app, double t_max);
int				calculate_light_color(t_hit_record *hit, t_app *app);
double			calc_kd(const t_hit_record *hit, t_vec3 light_dir,
					double atten);
double			calc_ks(const t_hit_record *hit, t_vec3 light_dir,
					t_vec3 view_dir, double atten);

#endif