/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_n_cpy_gc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:56:33 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 15:13:04 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"
#include "ft_string.h"

char	*str_n_cpy_gc(t_list *gc, const char *src, size_t len)
{
	char	*dst;

	dst = ft_gc_malloc(gc, len + 1);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, src, len + 1);
	return (dst);
}
