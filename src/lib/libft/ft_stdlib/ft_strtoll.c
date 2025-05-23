/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:31:44 by teando            #+#    #+#             */
/*   Updated: 2024/12/15 17:34:46 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_string.h"
#include <errno.h>
#include <limits.h>
#include <stddef.h>

static int	parse_base_and_sign(const char **str, int base, int *sign)
{
	*sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*sign = -1;
		(*str)++;
	}
	if (base == 0)
	{
		if (**str == '0')
		{
			(*str)++;
			if (**str == 'x' || **str == 'X')
			{
				(*str)++;
				return (16);
			}
			return (8);
		}
		return (10);
	}
	if (base == 16 && **str == '0' && (*(*str + 1) == 'x' || *(*str
				+ 1) == 'X'))
		*str += 2;
	return (base);
}

static int	convert_digit(char c, int base)
{
	const char	*digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char	*p;

	p = ft_strchr(digits, ft_toupper(c));
	if (p && p - digits < base)
		return (p - digits);
	return (-1);
}

static void	handle_overflow(const char **str, int base,
		unsigned long long *result, int sign)
{
	errno = ERANGE;
	*result = (unsigned long long)LLONG_MAX + ((1 - sign) >> 1);
	while (convert_digit(**str, base) >= 0)
		(*str)++;
}

static long long	process_digits(const char **str, int base, int sign,
		char **endptr)
{
	unsigned long long	result;
	unsigned long long	cutoff;
	int					cutlim;
	int					digit;

	result = 0;
	cutoff = (unsigned long long)LLONG_MAX + ((1 - sign) >> 1);
	cutlim = cutoff % base;
	cutoff /= base;
	while (1)
	{
		digit = convert_digit(**str, base);
		if (digit < 0)
			break ;
		if (result > cutoff || (result == cutoff && digit > cutlim))
		{
			handle_overflow(str, base, &result, sign);
			break ;
		}
		result = result * base + digit;
		(*str)++;
	}
	if (endptr)
		*endptr = (char *)*str;
	return ((long long)sign * (long long)result);
}

long long	ft_strtoll(const char *nptr, char **endptr, int base)
{
	const char	*str;
	int			sign;
	long long	result;

	if (base < 0 || base == 1 || base > 36)
	{
		errno = EINVAL;
		if (endptr)
			*endptr = (char *)nptr;
		return (0);
	}
	while (ft_isspace(*nptr))
		nptr++;
	str = nptr;
	base = parse_base_and_sign(&str, base, &sign);
	result = process_digits(&str, base, sign, endptr);
	if (str == nptr)
	{
		if (endptr)
			*endptr = (char *)nptr;
		return (0);
	}
	return (result);
}
