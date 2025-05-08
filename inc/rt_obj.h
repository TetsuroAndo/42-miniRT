/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_obj.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:30:28 by teando            #+#    #+#             */
/*   Updated: 2025/05/08 21:14:58 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OBJ_H
# define RT_OBJ_H

# include "rt_vec.h"

typedef struct s_app	t_app;

/** 球 */
typedef struct s_sphere
{
	t_vec3				center;
	double				radius; /* .rt では diameter → radius = d / 2 */
	t_color				color;
}						t_sphere;

/** 平面 */
typedef struct s_plane
{
	t_vec3				point;  /* 任意一点 */
	t_vec3				normal; /* 正規化済み */
	t_color				color;
}						t_plane;

/** 円柱 (無限側面 + 切り取り高さ) */
typedef struct s_cylinder
{
	t_vec3				center; /* 中心 (胴体軸の midpoint) */
	t_vec3				axis;   /* 正規化軸ベクトル */
	double				radius;
	double				height;
	t_color				color;
}						t_cylinder;

typedef struct s_obj	t_obj;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}						t_obj_type;

/** 汎用オブジェクト (単方向リスト) */
typedef struct s_obj
{
	t_obj_type			type;
	union
	{
		t_sphere		sp;
		t_plane			pl;
		t_cylinder		cy;
	} u;
	t_obj				*next;
	t_hit_record		(*hit)(t_obj *obj, t_ray *ray, t_app *app);
}						t_obj;

#endif
