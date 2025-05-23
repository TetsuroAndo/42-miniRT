/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:42:10 by teando            #+#    #+#             */
/*   Updated: 2025/05/09 03:22:57 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

/* 文字列からRGB色へ変換 */
int	parse_rgb(char **s, t_color *out)
{
	double	r;
	double	g;
	double	b;

	skip_ws(s);
	/* R成分をパース */
	if (!parse_f64(s, &r, 0, 255))
		return (0);
	/* カンマを期待 */
	if (!expect_char(s, ','))
		return (0);
	/* G成分をパース */
	if (!parse_f64(s, &g, 0, 255))
		return (0);
	/* カンマを期待 */
	if (!expect_char(s, ','))
		return (0);
	/* B成分をパース */
	if (!parse_f64(s, &b, 0, 255))
		return (0);
	out->r = (unsigned char)r;
	out->g = (unsigned char)g;
	out->b = (unsigned char)b;
	return (1);
}
