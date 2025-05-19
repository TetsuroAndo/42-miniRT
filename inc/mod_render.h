/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_render.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:20:32 by teando            #+#    #+#             */
/*   Updated: 2025/05/20 06:09:33 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_RENDER_H
# define MOD_RENDER_H

# include "xlib.h"
#include <math.h>

void					my_mlx_pixel_put(t_img *img, int x, int y, int color);
int						create_trgb(int t, int r, int g, int b);
t_vec3					get_ray_direction(t_camera *cam, int i, int j);

int						redraw_loop(void *param);
void					render(t_img *img, t_app *app);
void					draw(t_app *app);

/* shadow and lighting */
int						is_shadow(t_hit_record *hit, t_lights *light, t_app *app);
int						calculate_light_color(t_hit_record *hit, t_app *app);

/* clamp helper */
#define CLAMP255(x) ((x) > 255 ? 255 : (x))

/* debug */
void	temp(t_img *img);

#endif