/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_right.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:04:00 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 18:05:59 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_substr_r(const char *str, char delimiter)
{
	char	*pos;

	if (!str)
		return (NULL);
	pos = ft_strchr(str, delimiter);
	if (!pos)
		return (ft_strdup(""));
	return (ft_strdup(pos + 1));
}
