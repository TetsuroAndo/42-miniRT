/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:31:00 by tomsato           #+#    #+#             */
/*   Updated: 2025/04/30 19:06:59 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "xlib.h"

char	*xstrdup(const char *s1, t_app *app)
{
	char	*s2;
	size_t	size;

	size = ft_strlen(s1) + 1;
	s2 = (char *)xmalloc(size * sizeof(char), app);
	if (s2)
		ft_strlcpy(s2, s1, size);
	return (s2);
}