/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:26:10 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 11:02:13 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

/*
 * 円柱のパース (cy)
 *	- 識別子: `cy`
 *	- 円柱中心の `x,y,z` 座標: `50.0,0.0,20.6`
 *	- 円柱軸の 3D **正規化** ベクトル (各軸 `[-1,1]`): `0.0,0.0,1.0`
 *	- 円柱の直径: `14.2`
 *	- 円柱の高さ: `21.42`
 *	- `R,G,B` 色 `[0‑255]`: `10,0,255`
 */
void	parse_cylinder(char *line, t_scene *scene, t_app *app)
{
	t_obj	*obj;
	double	diameter;

	obj = (t_obj *)xcalloc(1, sizeof(t_obj), app);
	obj->type = OBJ_CYLINDER;
	obj->hit = cylinder_hit;
	obj->spec = (t_color){255, 255, 255};
	obj->shininess = 32.0;
	/* 中心座標 */
	if (!parse_vec3(&line, &obj->u.cy.center))
		exit_errmsg("cylinder: invalid center position", app);
	/* 軸ベクトル (正規化) */
	if (!parse_normal_vec3(&line, &obj->u.cy.axis))
		exit_errmsg("cylinder: invalid axis vector", app);
	/* 直径 */
	if (!parse_f64(&line, &diameter, 0.0, INFINITY))
		exit_errmsg("cylinder: invalid diameter", app);
	/* 直径から半径に変換 */
	obj->u.cy.radius = diameter / 2.0;
	/* 高さ */
	if (!parse_f64(&line, &obj->u.cy.height, 0.0, INFINITY))
		exit_errmsg("cylinder: invalid height", app);
	/* RGB色 */
	if (!parse_rgb(&line, &obj->u.cy.color))
		exit_errmsg("cylinder: invalid color", app);
	/* 反射率 */
	obj->reflect = 0.0;
	try_parse_reflect(&line, &obj->reflect);
	if (!expect_line_end(&line))
		exit_errmsg("cylinder: unexpected extra parameters", app);
	add_obj(&scene->objs, obj);
}
