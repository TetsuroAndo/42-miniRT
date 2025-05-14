/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xclose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:10:21 by teando            #+#    #+#             */
/*   Updated: 2025/05/09 03:22:28 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include <stdio.h>

int	xclose(int fd)
{
	int	ret;

	if (!fd || fd < 3)
		return (0);
	ret = close(fd);
	if (ret == -1)
		perror("close");
	fd = -1;
	return (ret);
}
