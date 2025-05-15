/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_hyperboloid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:35:00 by teando            #+#    #+#             */
/*   Updated: 2025/05/15 17:51:09 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"
#include <stdio.h>
/*
 * 双曲面のパース (hb)
 *	- 識別子: `hb`
 *	- 双曲面中心の `x,y,z` 座標: `50.0,0.0,20.6`
 *	- 双曲面軸の 3D **正規化** ベクトル (各軸 `[-1,1]`): `0.0,0.0,1.0`
 *	- x軸方向の半径: `10.0`
 *	- y軸方向の半径: `10.0`
 *	- z軸方向の係数: `5.0`
 *	- `R,G,B` 色 `[0‑255]`: `10,0,255`
 */
void	parse_hyperboloid(char *line, t_scene *scene, t_app *app)
{
	t_obj	*obj;

	obj = (t_obj *)xcalloc(1, sizeof(t_obj), app);
	obj->type = OBJ_HYPERBOLOID;
	obj->hit = hyperboloid_hit;
	/* 中心座標 */
	if (!parse_vec3(&line, &obj->u.hb.center))
		exit_errmsg("hyperboloid: invalid center position", app);
	/* 軸ベクトル (正規化) */
	if (!parse_normal_vec3(&line, &obj->u.hb.axis))
		exit_errmsg("hyperboloid: invalid axis vector", app);
	/* x軸方向の半径 */
	if (!parse_f64(&line, &obj->u.hb.a, 0.0, INFINITY))
		exit_errmsg("hyperboloid: invalid x-axis radius", app);
	/* y軸方向の半径 */
	if (!parse_f64(&line, &obj->u.hb.b, 0.0, INFINITY))
		exit_errmsg("hyperboloid: invalid y-axis radius", app);
	/* z軸方向の係数 */
	if (!parse_f64(&line, &obj->u.hb.c, 0.0, INFINITY))
		exit_errmsg("hyperboloid: invalid z-axis coefficient", app);
	/* RGB色 */
	if (!parse_rgb(&line, &obj->u.hb.color))
		exit_errmsg("hyperboloid: invalid color", app);
	if (!expect_line_end(&line))
		exit_errmsg("hyperboloid: unexpected extra parameters", app);
	add_obj(&scene->objs, obj);
}
