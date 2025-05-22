/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_f64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:36:19 by teando            #+#    #+#             */
/*   Updated: 2025/05/14 12:12:19 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

/* 数値範囲チェック（NaN、±INFも検出） */
static int	check_range_f64(double val, double min, double max)
{
	/* NaNや±INFの検出 */
	if (isnan(val) || isinf(val))
		return (0);
	return (min <= val && val <= max);
}

/*
 * 文字列から浮動小数点数へ変換
 * 注：デリミタ処理を行わず、数値のみを解析する
 *
 * @param s		入力文字列
 * @param out	出力値
 * @param min	最小値
 * @param max	最大値
 * @return		成功時1、失敗時0
 */
int	parse_f64(char **s, double *out, double min, double max)
{
	char	*endptr;

	skip_ws(s);
	*out = ft_strtod(*s, &endptr);
	if (endptr == *s || !check_range_f64(*out, min, max))
		return (0);
	*s = endptr;
	return (1);
}
