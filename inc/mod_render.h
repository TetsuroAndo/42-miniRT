/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_render.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:48:13 by teando            #+#    #+#             */
/*   Updated: 2025/05/14 12:59:32 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_RENDER_H
#define MOD_RENDER_H

#include "rt_vec.h"
#include "rt_obj.h"
#include "rt_scene.h"
#include "rt_render.h"

typedef struct s_img	t_img;

void my_mlx_pixel_put(t_img *img, int x, int y, int color);
int create_trgb(int t, int r, int g, int b);
t_vec3 get_ray_direction(t_camera *cam, int i, int j);

t_color ray_color(t_app *app, t_ray *ray);
int     ray_color_trgb(t_app *app, t_ray *ray);

void draw(t_app *app);

/* Vector helpers */
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, double s);

#endif
