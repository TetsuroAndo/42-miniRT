/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:41:43 by teando            #+#    #+#             */
/*   Updated: 2024/11/07 17:06:55 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include <limits.h>

long	ft_atol(const char *nptr)
{
	unsigned long	cutoff;
	int				neg;
	int				tmp;
	unsigned long	r;

	neg = 0;
	r = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		neg = *nptr++ == '-';
	cutoff = (unsigned long)LONG_MAX ^ -neg;
	while (ft_isdigit(*nptr))
	{
		r *= 10;
		tmp = *nptr++ - '0';
		if (r > cutoff || cutoff - r < (unsigned long)tmp)
			return (cutoff);
		r += tmp;
	}
	if (neg)
		return (-r);
	return (r);
}
