/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrs_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:14:34 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 23:44:30 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

int	ft_putstrs_fd(char **strs, char *delimiter, int fd)
{
	int		count;
	int		i;
	char	*str;

	if (!strs || !delimiter)
		return (0);
	count = 0;
	i = 0;
	while (strs[i])
	{
		if (i > 0)
			count += ft_putstr_fd(delimiter, fd);
		str = strs[i];
		count += ft_putstr_fd(str, fd);
		i++;
	}
	return (count);
}
