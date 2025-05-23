/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_left.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:02:52 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 18:05:41 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_substr_l(const char *str, char delimiter)
{
	char	*pos;
	size_t	key_len;

	if (!str)
		return (NULL);
	pos = ft_strchr(str, delimiter);
	if (!pos)
		return (ft_strdup(str));
	key_len = (size_t)(pos - str);
	return (ft_substr(str, 0, key_len));
}
