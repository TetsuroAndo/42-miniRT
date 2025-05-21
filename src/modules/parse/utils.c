/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:50:00 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 11:08:01 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

/**
 * 空白文字をスキップする
 * 
 * @param s 入力文字列ポインタのポインタ
 * @return 常に1（成功）
 */
void	skip_ws(char **s)
{
	while (**s && ft_isspace(**s))
		(*s)++;
}

/**
 * 期待する文字があるかチェックし、あれば次に進む
 * 
 * @param s 入力文字列ポインタのポインタ
 * @param c 期待する文字
 * @return 成功時1、失敗時0
 */
int	expect_char(char **s, char c)
{
	skip_ws(s);
	if (**s != c)
		return (0);
	(*s)++;
	return (1);
}

/*
 * 行末を期待 コメントは許容する
 * 
 * @param s 入力文字列ポインタのポインタ
 * @return 成功時1、失敗時0
 */
int	expect_line_end(char **s)
{
	if (!*s)
		return (1);
	skip_ws(s);
	return (**s == '\0' || **s == '#');
}

void	add_obj(t_obj **obj, t_obj *new)
{
	new->next = *obj;
	*obj = new;
}

/* 反射率 (0-1) があれば読む。失敗しても構文エラーにはしない */
int	try_parse_reflect(char **s, double *out)
{
	double r;
	char  *save = *s;

	skip_ws(s);
	if (!expect_char(s, ':'))
		return (0);
	skip_ws(s);
	if (!parse_f64(s, &r, 0.0, 1.0))
	{
		*s = save;
		return (0);
	}
	*out = r;
	return (1);
}
