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

static int	check_range_f64(double val, double min, double max)
{
	if (isnan(val) || isinf(val))
		return (0);
	return (min <= val && val <= max);
}

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
