/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:20:24 by teando            #+#    #+#             */
/*   Updated: 2024/11/07 17:20:26 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_utoa(unsigned int n)
{
	char	buffer[11];
	char	*c;

	c = &buffer[11];
	*--c = '\0';
	while (n || !*c)
	{
		*--c = n % 10 + '0';
		n /= 10;
	}
	return (ft_strdup(c));
}
