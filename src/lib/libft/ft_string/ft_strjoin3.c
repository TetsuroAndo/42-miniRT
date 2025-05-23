/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:01:14 by teando            #+#    #+#             */
/*   Updated: 2025/04/29 20:07:16 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*r;
	size_t	size;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	if (!s3)
		s3 = "";
	size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	r = (char *)malloc(sizeof(char) * size);
	if (!r)
		return (NULL);
	ft_strlcpy(r, s1, size);
	ft_strlcat(r, s2, size);
	ft_strlcat(r, s3, size);
	return (r);
}
