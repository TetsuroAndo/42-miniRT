/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 23:25:25 by teando            #+#    #+#             */
/*   Updated: 2024/11/07 17:01:50 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*r;

	if (!s || !f)
		return (NULL);
	i = 0;
	r = ft_strdup(s);
	if (r)
	{
		while (r[i])
		{
			r[i] = f(i, r[i]);
			i++;
		}
	}
	return (r);
}
