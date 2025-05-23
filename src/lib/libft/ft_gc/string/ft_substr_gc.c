/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_gc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:02:23 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 15:15:42 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"
#include "ft_string.h"

char	*ft_substr_gc(t_list *gc, const char *s, unsigned int start, size_t len)
{
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup_gc(gc, ""));
	if (len > slen - start)
		len = slen - start;
	return (str_n_cpy_gc(gc, s + start, len));
}

char	*ft_substr_r_gc(t_list *gc, const char *s, const char sep, size_t len)
{
	const char	*p;

	if (!s)
		return (NULL);
	p = ft_strchr(s, sep);
	if (!p)
		return (ft_strdup_gc(gc, ""));
	p++;
	if (!len)
		len = ft_strlen(p);
	return (str_n_cpy_gc(gc, p, len));
}

char	*ft_substr_l_gc(t_list *gc, const char *s, const char sep, size_t len)
{
	const char	*p;
	size_t		l;

	if (!s)
		return (NULL);
	p = ft_strchr(s, sep);
	if (!p)
		return (ft_strdup_gc(gc, ""));
	l = (size_t)(p - s);
	if (len && len < l)
		l = len;
	return (str_n_cpy_gc(gc, s, l));
}
