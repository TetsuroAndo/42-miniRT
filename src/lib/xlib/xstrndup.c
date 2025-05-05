/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrndup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:34:22 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/05 09:58:24 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include <stdlib.h>

char	*xstrndup(const char *s, size_t n, t_app *app)
{
	char	*r;
	size_t	len;

	r = (char *)xmalloc((n + 1) * sizeof(char), app);
	len = ft_strnlen(s, n);
	if (!r)
		return (NULL);
	r[len] = '\0';
	return (ft_memcpy(r, s, len));
}