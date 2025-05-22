/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_hit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:08:17 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/20 07:49:02 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_HIT_H
# define MOD_HIT_H

# include "xlib.h"
# include "rt_render.h"
# include "rt_vec.h"

typedef struct s_app	t_app;
typedef struct s_scene	t_scene;

# ifndef EPSILON
#  define EPSILON 1e-6
# endif

/* hit functions */
t_hit_record			cone_hit(t_obj *obj, t_ray ray, t_app *app);
t_hit_record			plane_hit(t_obj *obj, t_ray ray, t_app *app);
t_hit_record			cylinder_hit(t_obj *obj, t_ray ray, t_app *app);
t_hit_record			sphere_hit(t_obj *obj, t_ray ray, t_app *app);
t_hit_record			hyperboloid_hit(t_obj *obj, t_ray ray, t_app *app);
t_hit_record			paraboloid_hit(t_obj *obj, t_ray ray, t_app *app);

#endif