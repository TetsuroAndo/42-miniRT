/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:36:11 by teando            #+#    #+#             */
/*   Updated: 2025/05/05 02:15:16 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SCENE_H
# define RT_SCENE_H

# include "rt_vec.h"

/** 環境光 (A) */
typedef struct s_ambient
{
	double 			ratio; /* 0.0 – 1.0 */
	t_color			color;
}					t_ambient;

/** カメラ (C) */
typedef struct s_camera
{
	t_vec3			pos;
	t_vec3			dir; /* 正規化 */
	double			fov; /* ° */
}					t_camera;

/** 点光源 (L) 単方向リスト */
typedef struct s_light
{
	t_vec3			pos;
	double			bright; /* 0.0 – 1.0 */
	t_color			color; /* 未使用でも保持 */
	struct s_light	*next;
}					t_light;

typedef struct s_scene
{
	t_ambient		amb; /* A (一意) */
	t_camera		cam;  /* C (一意) */
	t_light			light; /* L (一意) */
	t_obj			*objs;   /* ジオメトリ可変 */
}					t_scene;

#endif