/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 03:12:33 by teando            #+#    #+#             */
/*   Updated: 2025/04/29 20:07:01 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include <stdio.h>

int	ft_putendl_fd(char *s, int fd)
{
	int	cnt;

	cnt = ft_putstr_fd(s, fd);
	if (cnt == EOF)
		return (EOF);
	if (ft_putchar_fd('\n', fd) == EOF)
		return (EOF);
	return (cnt + 1);
}
