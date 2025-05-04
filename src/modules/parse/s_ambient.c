/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_ambient.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:23:16 by teando            #+#    #+#             */
/*   Updated: 2025/05/05 01:18:34 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

/*
 * 環境光のパース (A)
 *	- 識別子: `A`
 *	- 環境光比率 `[0.0,1.0]`: `0.2`
 *	- `R,G,B` 色 `[0‑255]`: `255,255,255`
 */
void	parse_ambient(char *line, t_scene *scene, t_app *app)
{
	static int	seen_ambient = 0;

	/* 重複チェック */
	if (seen_ambient)
		exit_errmsg("duplicate ambient light", app);
	seen_ambient = 1;
	/* 環境光強度 (0.0-1.0) */
	if (!parse_f64(&line, &scene->amb.ratio, 0.0, 1.0))
		exit_errmsg("ambient: invalid ratio (expected 0.0-1.0)", app);
	/* RGB色 */
	if (!parse_rgb(&line, &scene->amb.color))
		exit_errmsg("ambient: invalid color (expected R,G,B in 0-255)", app);
	if (!expect_line_end(&line))
		exit_errmsg("ambient: unexpected extra parameters", app);
}
