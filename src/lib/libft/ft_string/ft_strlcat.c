/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 02:55:06 by teando            #+#    #+#             */
/*   Updated: 2024/11/07 17:32:58 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;

	if (dstsize == 0)
		return (ft_strlen(src));
	dst_len = ft_strnlen(dst, dstsize);
	src_len = ft_strlen(src);
	if (dstsize > dst_len)
	{
		dst += dst_len;
		while (*src && dst_len < dstsize - 1)
			*dst++ = (dstsize--, *src++);
		*dst = '\0';
	}
	return (dst_len + src_len);
}
