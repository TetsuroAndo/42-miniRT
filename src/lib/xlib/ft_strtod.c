/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:11:02 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/14 14:27:31 by teando           ###   ########.fr       */
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

double	ft_strtod(const char *nptr, char **endptr)
{
	long		b_dot;
	long		a_dot;
	double		result;
	int			digits;
	const char	*decimal_start;

	b_dot = ft_strtol(nptr, endptr, BASE);
	nptr = *endptr;
	if (*nptr == DOT)
	{
		nptr++;
		decimal_start = nptr;
		digits = 0;
		while (decimal_start[digits] && ft_isdigit(decimal_start[digits]))
			digits++;
		if (digits > 0)
		{
			a_dot = ft_strtol(decimal_start, endptr, BASE);
			result = b_dot + (a_dot / my_pow(10.0, digits));
			return (result);
		}
	}
	return (b_dot);
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