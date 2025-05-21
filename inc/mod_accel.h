/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_accel.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:53:32 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 10:21:02 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_ACCEL_H
# define MOD_ACCEL_H

# include "rt_obj.h"
# include "rt_vec.h"
# include "rt_scene.h"
# include "xlib.h"
# include <math.h>

typedef struct s_app	t_app;

typedef struct s_aabb
{
	t_vec3	min;
	t_vec3	max;
}	t_aabb;

typedef struct s_bvh
{
	t_aabb			box;
	struct s_bvh	*left;
	struct s_bvh	*right;
	t_obj			**objs;   /* 葉: 配列へのポインタ */
	int				obj_cnt;
}	t_bvh;

/* API */
int				make_bvh(t_scene *scene, t_app *app);
int				bvh_hit(t_bvh *node, t_ray r, double t_max, t_hit_record *out);

/* AABB functions */
t_aabb			aabb_merge(t_aabb a, t_aabb b);
int				aabb_hit(t_aabb box, t_ray r, double t_max);
t_aabb			obj_bbox(t_obj *o);

#endif
