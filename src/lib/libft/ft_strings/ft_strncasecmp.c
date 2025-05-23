/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncasecmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 03:18:07 by teando            #+#    #+#             */
/*   Updated: 2024/11/21 03:28:42 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include <stddef.h>

int	ft_strncasecmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	while (n--)
	{
		c1 = (unsigned char)ft_tolower((unsigned char)*s1++);
		c2 = (unsigned char)ft_tolower((unsigned char)*s2++);
		if (c1 != c2 || c1 == '\0')
			return (c1 - c2);
	}
	return (0);
}
