/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 03:26:20 by teando            #+#    #+#             */
/*   Updated: 2024/11/21 03:28:43 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"

int	ft_strcasecmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;

	while (1)
	{
		c1 = (unsigned char)ft_tolower((unsigned char)*s1++);
		c2 = (unsigned char)ft_tolower((unsigned char)*s2++);
		if (c1 != c2 || c1 == '\0')
			return (c1 - c2);
	}
	return (0);
}
