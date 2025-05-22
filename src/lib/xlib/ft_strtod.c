/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:11:02 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/14 16:01:09 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"

#define DOT '.'
#define BASE 10

static double	my_pow(double x, double y)
{
	double	result;
	double	i;

	result = x;
	i = 1;
	while (i < y)
	{
		result *= x;
		i++;
	}
	return (result);
}

static size_t	count_decimal_digits(const char *decimal_start)
{
	size_t	digits;

	digits = 0;
	while (decimal_start[digits] && ft_isdigit(decimal_start[digits]))
		digits++;
	return (digits);
}

double	ft_strtod(const char *nptr, char **endptr)
{
	long	a_dot;
	long	b_dot;
	size_t	digits;
	double	frac;

	b_dot = ft_strtol(nptr, endptr, BASE);
	nptr = *endptr;
	if (*nptr == DOT)
	{
		++nptr;
		digits = count_decimal_digits(nptr);
		*endptr = (char *)nptr + digits;
		if (digits > 0)
		{
			a_dot = ft_strtol(nptr, endptr, BASE);
			frac = (double)a_dot / my_pow(10.0, (double)digits);
			if (b_dot < 0)
				return ((double)b_dot - frac);
			return ((double)b_dot + frac);
		}
	}
	return ((double)b_dot);
}
