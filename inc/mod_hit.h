/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_hit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:08:17 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/15 17:09:38 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_HIT_H
# define MOD_HIT_H

typedef struct s_app	t_app;
typedef struct s_scene	t_scene;
/* hit functions */
t_hit_record			cone_hit(t_obj *obj, t_ray ray, t_app *app);
t_hit_record			plane_hit(t_obj *obj, t_ray ray, t_app *app);
t_hit_record			cylinder_hit(t_obj *obj, t_ray ray, t_app *app);
t_hit_record			cone_hit(t_obj *obj, t_ray ray, t_app *app);
t_hit_record			hyperboloid_hit(t_obj *obj, t_ray ray, t_app *app);
t_hit_record			paraboloid_hit(t_obj *obj, t_ray ray, t_app *app);

#endif