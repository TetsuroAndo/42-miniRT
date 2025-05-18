/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:31:00 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/15 22:10:37 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"

char	*xstrdup(const char *s1, t_app *app)
{
	char	*s2;

	s2 = ft_strdup(s1);
	if (ft_gc_track(app->gc, s2) < 0)
		exit_app(app, E_ALLOC);
	return (s2);
}
