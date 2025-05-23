/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 02:22:52 by teando            #+#    #+#             */
/*   Updated: 2025/04/29 20:07:22 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	if (!*little)
		return ((char *)big);
	if (!len || !*big)
		return (NULL);
	little_len = ft_strlen(little);
	while (little_len <= len--)
	{
		if (*big == *little && !ft_strncmp(big, little, little_len))
			return ((char *)big);
		big++;
	}
	return (NULL);
}
