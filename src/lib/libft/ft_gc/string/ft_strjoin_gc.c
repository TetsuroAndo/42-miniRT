/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_gc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:02:23 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 15:33:04 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"
#include "ft_string.h"

char	*ft_strjoin_gc(t_list *gc, const char *s1, const char *s2)
{
	size_t	len;
	char	*dst;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = ft_gc_malloc(gc, len);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, len);
	ft_strlcat(dst, s2, len);
	return (dst);
}

char	*ft_strjoin3_gc(t_list *gc, const char *s1, const char *s2,
		const char *s3)
{
	size_t	l;
	char	*dst;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	if (!s3)
		s3 = "";
	l = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	dst = ft_gc_malloc(gc, l);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, l);
	ft_strlcat(dst, s2, l);
	ft_strlcat(dst, s3, l);
	return (dst);
}
