/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 05:27:18 by teando            #+#    #+#             */
/*   Updated: 2024/12/06 16:18:28 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stddef.h>

char	*ft_strpbrk(const char *s, const char *accept)
{
	while (*s)
	{
		if (ft_strchr(accept, *s))
			return ((char *)s);
		s++;
	}
	return (NULL);
}
