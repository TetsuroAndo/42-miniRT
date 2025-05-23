/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 05:27:11 by teando            #+#    #+#             */
/*   Updated: 2024/12/06 17:21:10 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stddef.h>

char	*ft_strrev(char *str)
{
	char			*start;
	char			*end;
	char			temp;
	const size_t	len = ft_strlen(str);

	start = str;
	end = str + len;
	while (start < --end)
	{
		temp = *start;
		*start = *end;
		*end = temp;
		++start;
	}
	return (str);
}
