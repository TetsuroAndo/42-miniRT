/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_gc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:02:23 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 15:33:33 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"
#include "ft_string.h"

char	*ft_strdup_gc(t_list *gc, const char *s1)
{
	if (s1)
		return (str_n_cpy_gc(gc, s1, ft_strlen(s1)));
	return (NULL);
}

char	*ft_strndup_gc(t_list *gc, const char *s1, size_t n)
{
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (len > n)
		len = n;
	return (str_n_cpy_gc(gc, s1, len));
}
