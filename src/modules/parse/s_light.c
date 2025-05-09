/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:23:51 by teando            #+#    #+#             */
/*   Updated: 2025/05/08 15:03:40 by tomsato          ###   ########.fr       */
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
	static int	seen_light = 0;
	t_light		*light;

	/* 重複チェック */
	if (seen_light)
		exit_errmsg("duplicate light", app);
	seen_light = 1;
	light = &scene->light;
	if (!parse_vec3(&line, &light->pos))
		exit_errmsg("light: invalid position (expected x,y,z)", app);
	if (!parse_f64(&line, &light->bright, 0.0, 1.0))
		exit_errmsg("light: invalid brightness (expected 0.0-1.0)", app);
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
	light->next = NULL;
}
