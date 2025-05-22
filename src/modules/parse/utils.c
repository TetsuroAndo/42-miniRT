/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:50:00 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 21:58:49 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

void	skip_ws(char **s)
{
	while (**s && ft_isspace(**s))
		(*s)++;
}

int	expect_char(char **s, char c)
{
	skip_ws(s);
	if (**s != c)
		return (0);
	(*s)++;
	return (1);
}

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

int	try_parse_reflect(char **s, double *out)
{
	double	r;
	char	*save;

	save = *s;
	if (!expect_char(s, ':'))
		return (0);
	if (!parse_f64(s, &r, 0.0, 1.0))
	{
		*s = save;
		return (0);
	}
	*out = r;
	return (1);
}
