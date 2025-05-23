/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:24:19 by teando            #+#    #+#             */
/*   Updated: 2025/04/29 20:07:23 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strtok(char *restrict s, const char *restrict sep)
{
	static char	*p;

	if (!s && !p)
		return (NULL);
	if (!s)
		s = p;
	s += ft_strspn(s, sep);
	if (!*s)
		return (p = 0);
	p = s + ft_strcspn(s, sep);
	if (*p)
		*p++ = 0;
	else
		p = 0;
	return (s);
}
