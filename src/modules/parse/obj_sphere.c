/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:24:58 by teando            #+#    #+#             */
/*   Updated: 2025/05/15 17:49:50 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

/*
 * 球体のパース (sp)
 *	- 識別子: `sp`
 *	- 球中心の `x,y,z` 座標: `0.0,0.0,20.6`
 *	- 球の直径: `12.6`
 *	- `R,G,B` 色 `[0‑255]`: `10,0,255`
 */
void	parse_sphere(char *line, t_scene *scene, t_app *app)
{
	t_obj	*obj;
	double	diameter;

	obj = (t_obj *)xcalloc(1, sizeof(t_obj), app);
	obj->type = OBJ_SPHERE;
	obj->hit = sphere_hit;
	/* 中心座標 */
	if (!parse_vec3(&line, &obj->u.sp.center))
		exit_errmsg("sphere: invalid center position", app);
	/* 直径 */
	if (!parse_f64(&line, &diameter, 0.0, INFINITY))
		exit_errmsg("sphere: invalid diameter", app);
	/* 直径から半径に変換 */
	obj->u.sp.radius = diameter / 2.0;
	/* RGB色 */
	if (!parse_rgb(&line, &obj->u.sp.color))
		exit_errmsg("sphere: invalid color", app);
	if (!expect_line_end(&line))
		exit_errmsg("sphere: unexpected extra parameters", app);
	add_obj(&scene->objs, obj);
}
