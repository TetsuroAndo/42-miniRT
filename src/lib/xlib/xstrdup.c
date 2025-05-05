/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:31:00 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/05 09:58:20 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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