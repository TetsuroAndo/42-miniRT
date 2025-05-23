/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 03:22:15 by teando            #+#    #+#             */
/*   Updated: 2025/04/29 20:07:04 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"
#include <stdio.h>

int	ft_putstr_fd(char *s, int fd)
{
	int	count;

	if (!*s)
		return (0);
	count = write(fd, s, ft_strlen(s));
	if (count == -1)
		return (EOF);
	return (count);
}
