/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:30:00 by teando            #+#    #+#             */
/*   Updated: 2025/05/15 17:48:56 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"
#include <stdio.h>

/*
 * 円錐のパース (co)
 *	- 識別子: `co`
 *	- 円錐頂点の `x,y,z` 座標: `50.0,0.0,20.6`
 *	- 円錐軸の 3D **正規化** ベクトル (各軸 `[-1,1]`): `0.0,0.0,1.0`
 *	- 円錐の半頂角 (度): `30.0`
 *	- 円錐の高さ: `21.42`
 *	- `R,G,B` 色 `[0‑255]`: `10,0,255`
 */
void	parse_cone(char *line, t_scene *scene, t_app *app)
{
	t_obj	*obj;
	double	angle_deg;

	obj = (t_obj *)xcalloc(1, sizeof(t_obj), app);
	obj->type = OBJ_CONE;
	obj->hit = cone_hit;
	/* 頂点座標 */
	if (!parse_vec3(&line, &obj->u.co.vertex))
		exit_errmsg("cone: invalid vertex position", app);
	/* 軸ベクトル (正規化) */
	if (!parse_normal_vec3(&line, &obj->u.co.axis))
		exit_errmsg("cone: invalid axis vector", app);
	/* 半頂角 (度からラジアンに変換) */
	if (!parse_f64(&line, &angle_deg, 0.0, 90.0))
		exit_errmsg("cone: invalid angle (must be between 0 and 90 degrees)", app);
	obj->u.co.angle = angle_deg * M_PI / 180.0;
	/* 高さ */
	if (!parse_f64(&line, &obj->u.co.height, 0.0, INFINITY))
		exit_errmsg("cone: invalid height", app);
	/* RGB色 */
	if (!parse_rgb(&line, &obj->u.co.color))
		exit_errmsg("cone: invalid color", app);
	if (!expect_line_end(&line))
		exit_errmsg("cone: unexpected extra parameters", app);
	add_obj(&scene->objs, obj);
}
