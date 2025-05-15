/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:10:19 by teando            #+#    #+#             */
/*   Updated: 2025/05/15 22:45:59 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include <fcntl.h>

int xopen(char *pathname, int flags, t_app *app)
{
	int fd;

	fd = open(pathname, flags);
	if (fd == -1)
	{
		perror("open");
		exit_app(app, E_SYSTEM);
	}
	return (fd);
}
