/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_obj.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:30:28 by teando            #+#    #+#             */
/*   Updated: 2025/04/25 16:54:38 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OBJ_H
# define RT_OBJ_H

/** 3 次元ベクトル */
typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

/** 8‑bit RGB カラー */
typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct s_ray
{
	t_vec3			orig; /* 発射点 */
	t_vec3			dir;  /* 正規化済み方向 */
}					t_ray;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}					t_obj_type;

/** 球 */
typedef struct s_sphere
{
	t_vec3			center;
	double			radius; /* .rt では diameter → radius = d / 2 */
	t_color			color;
}					t_sphere;

/** 平面 */
typedef struct s_plane
{
	t_vec3			point;  /* 任意一点 */
	t_vec3			normal; /* 正規化済み */
	t_color			color;
}					t_plane;

/** 円柱 (無限側面 + 切り取り高さ) */
typedef struct s_cylinder
{
	t_vec3			center; /* 中心 (胴体軸の midpoint) */
	t_vec3			axis;   /* 正規化軸ベクトル */
	double			radius;
	double			height;
	t_color			color;
}					t_cylinder;

/** 汎用オブジェクト (単方向リスト) */
typedef struct s_object
{
	t_obj_type		type;
	union
	{
		t_sphere	sp;
		t_plane		pl;
		t_cylinder	cy;
	} u;
	struct s_object	*next;
}					t_object;

/** 環境光 (A) */
typedef struct s_ambient
{
	double			ratio; /* 0.0 – 1.0 */
	t_color			color;
}					t_ambient;

/** 点光源 (L) 単方向リスト */
typedef struct s_light
{
	t_vec3			pos;
	double			bright; /* 0.0 – 1.0 */
	t_color			color; /* 未使用でも保持 */
	struct s_light	*next;
}					t_light;

/** カメラ (C) */
typedef struct s_camera
{
	t_vec3			pos;
	t_vec3			dir; /* 正規化 */
	double			fov; /* ° */
}					t_camera;

typedef struct s_scene
{
	t_ambient		amb;   /* A (一意) */
	t_camera		cam;    /* C (一意) */
	t_light			*lights; /* L (可変) */
	t_object		*objs;  /* ジオメトリ可変 */
}					t_scene;

/* 画像バッファ */
typedef struct s_img
{
	void			*ptr; /* mlx_new_image */
	char			*px;  /* data addr */
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_img;

#endif
