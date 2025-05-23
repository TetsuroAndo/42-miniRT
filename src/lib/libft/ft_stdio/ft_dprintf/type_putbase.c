/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_putbase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:32:43 by teando            #+#    #+#             */
/*   Updated: 2024/11/10 10:48:32 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ul_putbase(int fd, unsigned long nbr, char *base, size_t base_len)
{
	int	len;
	int	r;

	if (nbr >= base_len)
	{
		len = ul_putbase(fd, nbr / base_len, base, base_len);
		r = type_putchar(fd, base[nbr % base_len]);
		if (r == -1)
			return (-1);
		return (len + r);
	}
	return (type_putchar(fd, base[nbr]));
}

int	type_putbase(int fd, long long nbr, char *base)
{
	int		r;
	int		cnt;
	size_t	base_len;

	cnt = 0;
	base_len = ft_strlen(base);
	if (nbr < 0)
	{
		r = type_putchar(fd, '-');
		if (r == -1)
			return (-1);
		cnt = r;
		nbr = -nbr;
	}
	r = ul_putbase(fd, nbr, base, base_len);
	if (r == -1)
		return (-1);
	return (cnt + r);
}
