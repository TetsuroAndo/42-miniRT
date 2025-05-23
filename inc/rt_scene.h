/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:36:11 by teando            #+#    #+#             */
/*   Updated: 2025/05/24 00:35:53 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SCENE_H
# define RT_SCENE_H

# include "rt_obj.h"
# include "rt_vec.h"

typedef struct s_ambient
{
	int				flag;
	double			ratio;
	t_color			color;
}					t_ambient;

typedef struct s_camera
{
	int				flag;
	t_vec3			pos;
	t_vec3			dir;
	double			fov;
}					t_camera;

typedef struct s_lights
{
	t_vec3			pos;
	double			bright;
	t_color			color;
	struct s_lights	*next;
}					t_lights;

typedef struct s_scene
{
	t_ambient		amb;
	t_camera		cam;
	t_lights		*lights;
	t_obj			*objs;
}					t_scene;

#endif