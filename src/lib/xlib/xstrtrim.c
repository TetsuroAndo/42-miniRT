/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrtrim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:35:55 by teando            #+#    #+#             */
/*   Updated: 2025/05/05 02:22:07 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"

char	*xstrtrim(char const *s1, char const *set, t_app *app)
{
	char	*trimmed;

	trimmed = ft_strtrim(s1, set);
	if (ft_gc_track(app->gc, trimmed) < 0)
		exit_app(app, E_ALLOC);
	if (trimmed == NULL)
		exit_app(app, E_ALLOC);
	return (trimmed);
}
