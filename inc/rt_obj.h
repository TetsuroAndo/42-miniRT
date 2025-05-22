/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_obj.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:30:28 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 23:36:29 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OBJ_H
# define RT_OBJ_H

# include "rt_vec.h"

typedef struct s_app		t_app;
typedef struct s_obj		t_obj;
typedef struct s_hit_record	t_hit_record;
typedef struct s_ray		t_ray;

typedef struct s_sphere
{
	t_vec3					center;
	double					radius;
	t_color					color;
}							t_sphere;

typedef struct s_plane
{
	t_vec3					point;
	t_vec3					normal;
	t_color					color;
}							t_plane;

typedef struct s_cylinder
{
	t_vec3					center;
	t_vec3					axis;
	double					radius;
	double					height;
	t_color					color;
}							t_cylinder;

typedef struct s_cone
{
	t_vec3					vertex;
	t_vec3					axis;
	double					angle;
	double					height;
	t_color					color;
}							t_cone;

typedef struct s_hyperboloid
{
	t_vec3					center;
	t_vec3					axis;
	double					a;
	double					b;
	double					c;
	t_color					color;
}							t_hyperboloid;

typedef struct s_paraboloid
{
	t_vec3					vertex;
	t_vec3					axis;
	double					k;
	double					height;
	t_color					color;
}							t_paraboloid;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE,
	OBJ_HYPERBOLOID,
	OBJ_PARABOLOID
}							t_obj_type;

struct						s_obj
{
	t_obj_type				type;
	union
	{
		t_sphere			sp;
		t_plane				pl;
		t_cylinder			cy;
		t_cone				co;
		t_hyperboloid		hb;
		t_paraboloid		pb;
	} u_type;
	t_color					spec;
	double					shininess;
	double					reflect;
	struct s_obj			*next;
	t_hit_record			(*hit)(struct s_obj * obj, t_ray ray, t_app * app);
};

#endif
