/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndupex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:21:00 by teando            #+#    #+#             */
/*   Updated: 2024/12/18 17:22:35 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

char	*ft_strndupex(const char *s, size_t n)
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
