/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_paraboloid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:40:00 by teando            #+#    #+#             */
/*   Updated: 2025/05/09 17:40:00 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"
#include <stdio.h>

/*
 * 放物面のパース (pb)
 *	- 識別子: `pb`
 *	- 放物面頂点の `x,y,z` 座標: `50.0,0.0,20.6`
 *	- 放物面軸の 3D **正規化** ベクトル (各軸 `[-1,1]`): `0.0,0.0,1.0`
 *	- 開口度: `0.1`
 *	- 高さ: `20.0`
 *	- `R,G,B` 色 `[0‑255]`: `10,0,255`
 */
void	parse_paraboloid(char *line, t_scene *scene, t_app *app)
{
	t_obj	*obj;

	obj = (t_obj *)xmalloc(sizeof(t_obj), app);
	obj->type = OBJ_PARABOLOID;
	/* 頂点座標 */
	if (!parse_vec3(&line, &obj->u.pb.vertex))
		exit_errmsg("paraboloid: invalid vertex position", app);
	/* 軸ベクトル (正規化) */
	if (!parse_normal_vec3(&line, &obj->u.pb.axis))
		exit_errmsg("paraboloid: invalid axis vector", app);
	/* 開口度 */
	if (!parse_f64(&line, &obj->u.pb.k, 0.0, INFINITY))
		exit_errmsg("paraboloid: invalid aperture coefficient", app);
	/* 高さ */
	if (!parse_f64(&line, &obj->u.pb.height, 0.0, INFINITY))
		exit_errmsg("paraboloid: invalid height", app);
	/* RGB色 */
	if (!parse_rgb(&line, &obj->u.pb.color))
		exit_errmsg("paraboloid: invalid color", app);
	if (!expect_line_end(&line))
		exit_errmsg("paraboloid: unexpected extra parameters", app);
	add_obj(&scene->objs, obj);
}
