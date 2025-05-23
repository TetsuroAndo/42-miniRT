/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_gc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:29:59 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 15:33:35 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"
#include "ft_string.h"
#include "ft_utils.h"

char	*ft_strtrim_gc(t_list *gc, const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_isinset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_isinset(s1[end - 1], set))
		end--;
	len = end - start;
	return (str_n_cpy_gc(gc, s1 + start, len));
}
