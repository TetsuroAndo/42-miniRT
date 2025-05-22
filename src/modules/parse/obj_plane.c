/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:25:41 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 22:18:57 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

/*
 * 平面のパース (pl)
 *	- 識別子: `pl`
 *	- 平面上の点: `0.0,0.0,20.6`
 *	- 法線ベクトル (正規化): `0.0,1.0,0.0`
 *	- `R,G,B` 色 `[0‑255]`: `10,0,255`
 */
void	parse_plane(char *line, int lnum, t_scene *scene, t_app *app)
{
	t_obj	*obj;

	obj = (t_obj *)xcalloc(1, sizeof(t_obj), app);
	obj->type = OBJ_PLANE;
	obj->hit = plane_hit;
	obj->spec = (t_color){255, 255, 255};
	obj->shininess = 0.0;
	/* 平面上の点 */
	if (!parse_vec3(&line, &obj->u_type.pl.point))
		exit_errmsg("plane: invalid point", lnum, app);
	/* 法線ベクトル (正規化) */
	if (!parse_normal_vec3(&line, &obj->u_type.pl.normal))
		exit_errmsg("plane: invalid normal vector", lnum, app);
	/* RGB色 */
	if (!parse_rgb(&line, &obj->u_type.pl.color))
		exit_errmsg("plane: invalid color", lnum, app);
	/* 反射率 */
	obj->reflect = 0.0;
	try_parse_reflect(&line, &obj->reflect);
	if (!expect_line_end(&line))
		exit_errmsg("plane: unexpected extra parameters", lnum, app);
	add_obj(&scene->objs, obj);
}
