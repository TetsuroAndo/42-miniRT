/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:25:41 by teando            #+#    #+#             */
/*   Updated: 2025/05/10 19:57:53 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

t_hit_record	plane_hit(t_obj *obj, t_ray ray, t_app *app)
{
	t_hit_record	result;
	
	result.t = INFINITY;
	
	return (result);
}

/*
 * 平面のパース (pl)
 *	- 識別子: `pl`
 *	- 平面上の点: `0.0,0.0,20.6`
 *	- 法線ベクトル (正規化): `0.0,1.0,0.0`
 *	- `R,G,B` 色 `[0‑255]`: `10,0,255`
 */
void	parse_plane(char *line, t_scene *scene, t_app *app)
{
	t_obj	*obj;

	obj = (t_obj *)xmalloc(sizeof(t_obj), app);
	obj->type = OBJ_PLANE;
	obj->hit = plane_hit();
	/* 平面上の点 */
	if (!parse_vec3(&line, &obj->u.pl.point))
		exit_errmsg("plane: invalid point", app);
	/* 法線ベクトル (正規化) */
	if (!parse_normal_vec3(&line, &obj->u.pl.normal))
		exit_errmsg("plane: invalid normal vector", app);
	/* RGB色 */
	if (!parse_rgb(&line, &obj->u.pl.color))
		exit_errmsg("plane: invalid color", app);
	if (!expect_line_end(&line))
		exit_errmsg("plane: unexpected extra parameters", app);
	add_obj(&scene->objs, obj);
}
