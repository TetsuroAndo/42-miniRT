/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:10:19 by teando            #+#    #+#             */
/*   Updated: 2025/05/05 09:58:14 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"

int xopen(char *pathname, int flags, t_app *app)
{
	int fd;

	fd = open(pathname, flags);
	if (fd == -1)
		exit_app(app, E_SYSTEM);
	return (fd);
}
