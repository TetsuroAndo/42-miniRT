/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:23:31 by teando            #+#    #+#             */
/*   Updated: 2025/05/24 00:22:46 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

/*
 * カメラのパース (C)
 *	- 識別子: `C`
 *	- 視点の `x,y,z` 座標: `-50.0,0,20`
 *	- 3D 正規化方向ベクトル (各軸 `[-1,1]`): `0.0,0.0,1.0`
 *	- FOV: 水平視野角 `[0,180]` 度: `70`
 */
void	parse_camera(char *line, int lnum, t_scene *scene, t_app *app)
{
	/* 重複チェック */
	if (scene->cam.flag)
		exit_errmsg("duplicate camera", lnum, app);
	scene->cam.flag = 1;
	/* 視点位置 */
	if (!parse_vec3(&line, &scene->cam.pos))
		exit_errmsg("camera: invalid position (expected x,y,z)", lnum, app);
	/* 方向ベクトル (正規化) */
	if (!parse_normal_vec3(&line, &scene->cam.dir))
		exit_errmsg("camera: invalid direction (expected normalized x,y,z)",
			lnum, app);
	/* 視野角 (FOV) */
	if (!parse_f64(&line, &scene->cam.fov, 0.0, 180.0))
		exit_errmsg("camera: invalid FOV (expected 0-180)", lnum, app);
	if (!expect_line_end(&line))
		exit_errmsg("camera: unexpected extra parameters", lnum, app);
}
