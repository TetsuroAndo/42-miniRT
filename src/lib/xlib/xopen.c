/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:10:19 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 20:25:26 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include <fcntl.h>

int	xopen(char *pathname, int flags, t_app *app)
{
	int	fd;

	fd = open(pathname, flags);
	if (fd == -1)
	{
		perror("open");
		exit_app(app, E_SYSTEM);
	}
	return (fd);
}
