/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:11:02 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/23 23:03:38 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"

#define DOT '.'
#define BASE 10

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
	int		sign;

	sign = 1;
	if (*nptr == '-')
		sign = -1;
	b_dot = ft_strtol(nptr, endptr, BASE);
	nptr = *endptr;
	if (*nptr == DOT)
	{
		digits = count_decimal_digits(++nptr);
		*endptr = (char *)nptr + digits;
		if (digits > 0)
		{
			a_dot = ft_strtol(nptr, endptr, BASE);
			frac = (double)a_dot / pow(10.0, (double)digits);
			if (b_dot < 0)
				return (((double)b_dot - frac));
			return (sign * ((double)b_dot + frac));
		}
	}
	return ((double)b_dot);
}
