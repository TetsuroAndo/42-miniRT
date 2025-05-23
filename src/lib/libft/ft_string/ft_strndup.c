/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:04:07 by teando            #+#    #+#             */
/*   Updated: 2024/11/07 17:33:10 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

char	*ft_strndup(const char *s, size_t n)
{
	char	*r;
	size_t	len;

	r = (char *)malloc((n + 1) * sizeof(char));
	len = ft_strnlen(s, n);
	if (!r)
		return (NULL);
	r[len] = '\0';
	return (ft_memcpy(r, s, len));
}
