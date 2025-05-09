/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_obj.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:30:28 by teando            #+#    #+#             */
/*   Updated: 2025/05/09 17:25:33 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OBJ_H
# define RT_OBJ_H

# include "rt_vec.h"

typedef struct s_app		t_app;
typedef struct s_obj		t_obj;
typedef struct s_hit_record	t_hit_record;

/* 球 */
typedef struct s_sphere
{
	t_vec3				center;
	double				radius; /* .rt では diameter → radius = d / 2 */
	t_color				color;
}						t_sphere;

/* 平面 */
typedef struct s_plane
{
	t_vec3				point;  /* 任意一点 */
	t_vec3				normal; /* 正規化済み */
	t_color				color;
}						t_plane;

/* 円柱 (無限側面 + 切り取り高さ) */
typedef struct s_cylinder
{
	t_vec3				center; /* 中心 (胴体軸の midpoint) */
	t_vec3				axis;   /* 正規化軸ベクトル */
	double				radius;
	double				height;
	t_color				color;
}						t_cylinder;

/* 円錐 */
typedef struct s_cone
{
	t_vec3				vertex; /* 頂点 */
	t_vec3				axis;   /* 正規化軸ベクトル */
	double				angle;  /* 半頂角（ラジアン） */
	double				height; /* 高さ */
	t_color				color;
}						t_cone;

/* 双曲面 */
typedef struct s_hyperboloid
{
	t_vec3				center; /* 中心 */
	t_vec3				axis;   /* 正規化軸ベクトル */
	double				a;      /* x軸方向の半径 */
	double				b;      /* y軸方向の半径 */
	double				c;      /* z軸方向の係数 */
	t_color				color;
}						t_hyperboloid;

/* 放物面 */
typedef struct s_paraboloid
{
	t_vec3				vertex; /* 頂点 */
	t_vec3				axis;   /* 正規化軸ベクトル */
	double				k;      /* 開口度 */
	double				height; /* 高さ */
	t_color				color;
}						t_paraboloid;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE,
	OBJ_HYPERBOLOID,
	OBJ_PARABOLOID
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
		t_cone			co;
		t_hyperboloid	hb;
		t_paraboloid	pb;
	} u;
	t_obj				*next;
	t_hit_record		(*hit)(t_obj *obj, t_ray *ray, t_app *app);
}						t_obj;

#endif
