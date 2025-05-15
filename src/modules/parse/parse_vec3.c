/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:42:22 by teando            #+#    #+#             */
/*   Updated: 2025/05/14 11:06:09 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"
#include <stdio.h>

/* 文字列から3次元ベクトルへ変換 */
int	parse_vec3(char **s, t_vec3 *out)
{
	skip_ws(s);
	/* X成分をパース */
	if (!parse_f64(s, &out->x, -INFINITY, INFINITY))
		return (0);
	/* カンマを期待 */
	if (!expect_char(s, ','))
		return (0);
	/* Y成分をパース */
	if (!parse_f64(s, &out->y, -INFINITY, INFINITY))
		return (0);
	/* カンマを期待 */
	if (!expect_char(s, ','))
		return (0);
	/* Z成分をパース */
	if (!parse_f64(s, &out->z, -INFINITY, INFINITY))
		return (0);
	return (1);
}

/* 正規化ベクトルのパース */
int	parse_normal_vec3(char **s, t_vec3 *out)
{
	double	len;

	if (!parse_vec3(s, out))
		return (0);
	/* 各成分が-1.0～1.0の範囲内かチェック */
	if (out->x < -1.0 || out->x > 1.0 || out->y < -1.0 || out->y > 1.0
		|| out->z < -1.0 || out->z > 1.0)
		return (0);
	/* ゼロベクトルでないことを確認 */
	if (out->x == 0.0 && out->y == 0.0 && out->z == 0.0)
		return (0);
	/* 正規化 */
	len = sqrt(out->x * out->x + out->y * out->y + out->z * out->z);
	/* 数値的に不安定なケースをチェック */
	if (len < 1e-6)
		return (0);
	out->x /= len;
	out->y /= len;
	out->z /= len;
	return (1);
}
