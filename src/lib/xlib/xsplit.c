/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xsplit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:55:23 by tomsato           #+#    #+#             */
/*   Updated: 2025/04/30 19:11:19 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "xlib.h"
#include <stdlib.h>

static char	**xnsplit(const char *s, char c, size_t len, t_app *app)
{
	char	**r;
	char	**r_head;

	r_head = (char **)xcalloc(len + 1, sizeof(char *), app);
	r = r_head;
	while (r_head && len--)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		*r = (char *)s;
		while (*s && *s != c)
			s++;
		*r = xstrndup(*r, s - *r, app);
		if (!*r++)
		{
			while (r_head <= r - 1)
				xfree((void **)(--r - 1), app);
			xfree((void **)&r_head, app);
			return (NULL);
		}
	}
	return (r_head);
}

char	**xsplit(char const *s, char c, t_app *app)
{
	return (xnsplit(s, c, ft_count_words(s, c), app));
}
