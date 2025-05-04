/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrtrim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:35:55 by teando            #+#    #+#             */
/*   Updated: 2025/05/04 22:10:55 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"

char	*xstrtrim(char const *s1, char const *set, t_app *app)
{
	char	*trimmed;

	trimmed = ft_strtrim(s1, set);
	ft_gc_track(app->gc, trimmed);
	if (!trimmed)
		exit_app(app, E_ALLOC);
	return (trimmed);
}
