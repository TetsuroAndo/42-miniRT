/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:14:32 by teando            #+#    #+#             */
/*   Updated: 2024/11/07 17:22:28 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include <stddef.h>

char	*ft_ltoa(long n)
{
	char			buffer[21];
	unsigned long	un;
	char			*c;

	c = &buffer[21];
	*--c = '\0';
	un = ft_abs(n);
	while (un || !*c)
	{
		*--c = un % 10 + '0';
		un /= 10;
	}
	if (n < 0)
		*--c = '-';
	return (ft_strdup(c));
}
