/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrndup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:34:22 by tomsato           #+#    #+#             */
/*   Updated: 2025/04/30 19:11:34 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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