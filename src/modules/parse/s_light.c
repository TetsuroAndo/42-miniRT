/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:23:51 by teando            #+#    #+#             */
/*   Updated: 2025/05/14 17:27:28 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

/*
 * 光源のパース (L)
 *	- 識別子: `L`
 *	- 光源 `x,y,z` 座標: `-40.0,50.0,0.0`
 *	- 光源の明度比率 `[0.0,1.0]`: `0.6`
 *	- (必須パートでは未使用) `R,G,B` 色 `[0‑255]`: `10,0,255`
 */
void	parse_light(char *line, t_scene *scene, t_app *app)
{
	t_lights	*light;

	light = (t_lights *)xcalloc(1, sizeof(t_lights), app);
	/* 位置 */
	if (!parse_vec3(&line, &light->pos))
		exit_errmsg("light: invalid position (expected x,y,z)", app);
	/* 明度比率 */
	if (!parse_f64(&line, &light->bright, 0.0, 1.0))
		exit_errmsg("light: invalid brightness (expected 0.0-1.0)", app);
	/* RGB色（オプション） */
	if (*line && !expect_line_end(&line))
	{
		if (!parse_rgb(&line, &light->color))
			exit_errmsg("light: invalid color (expected R,G,B in 0-255)", app);
	}
	/* default color: white */
	else
		light->color = (t_color){255, 255, 255};
	if (!expect_line_end(&line))
		exit_errmsg("light: unexpected extra parameters", app);
	/* 光源をリストに追加（先頭に追加） */
	light->next = scene->lights;
	scene->lights = light;
}
