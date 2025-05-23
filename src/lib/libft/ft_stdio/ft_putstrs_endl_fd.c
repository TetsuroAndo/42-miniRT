/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrs_endl_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:38:31 by teando            #+#    #+#             */
/*   Updated: 2025/04/29 20:07:07 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include <stdio.h>

int	ft_putstrs_endl_fd(char **strs, char *delimiter, int fd)
{
	int	count;

	if (!strs || !delimiter)
		return (0);
	count = ft_putstrs_fd(strs, delimiter, fd);
	if (count == EOF)
		return (EOF);
	if (ft_putchar_fd('\n', fd) == EOF)
		return (EOF);
	return (count + 1);
}
