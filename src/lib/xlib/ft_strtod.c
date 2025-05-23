/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:11:02 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/23 22:06:22 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"

#define DOT '.'
#define BASE 10

/* 小数点以降の桁数をカウントする関数 */
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

/*
#include "xlib.h"
#include <stdio.h>

int	main(void)
{
	const char *test_cases[] = {"123.456", "0.123", "42.0", "3.14159", "-1.23",
		"999999.999999", "0.0", "invalid", NULL};

	for (int i = 0; test_cases[i]; i++)
	{
		char *endptr;
		double result = ft_strtod(test_cases[i], &endptr);
		printf("Input: %-15s | Result: %f | Endptr: %s\n", test_cases[i],
			result, endptr);
	}

	// Compare with standard strtod
	printf("\nComparing with standard strtod:\n");
	const char *compare = "123.456";
	char *endptr1, *endptr2;
	double val1 = ft_strtod(compare, &endptr1);
	double val2 = strtod(compare, &endptr2);
	printf("ft_strtod: %f\nstrtod:    %f\n", val1, val2);

	return (0);
}
*/