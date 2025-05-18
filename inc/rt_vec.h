/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:35:22 by teando            #+#    #+#             */
/*   Updated: 2025/05/15 17:53:33 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VEC_H
# define RT_VEC_H

#include "math.h"

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

#endif