/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_putptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:33:45 by teando            #+#    #+#             */
/*   Updated: 2024/11/10 10:48:41 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	uintptr_putbase(int fd, uintptr_t nbr, char *base, size_t base_len)
{
	int	len;
	int	r;

	if (nbr >= base_len)
	{
		len = uintptr_putbase(fd, nbr / base_len, base, base_len);
		r = type_putchar(fd, base[nbr % base_len]);
		if (r == -1)
			return (-1);
		return (len + r);
	}
	return (type_putchar(fd, base[nbr]));
}

int	type_putptr(int fd, uintptr_t nbr, char *base)
{
	int		r;
	int		cnt;
	size_t	base_len;

	if (!nbr)
		return (type_putstr(fd, "(nil)"));
	r = type_putstr(fd, "0x");
	if (r == -1)
		return (-1);
	cnt = r;
	base_len = ft_strlen(base);
	r = uintptr_putbase(fd, nbr, base, base_len);
	if (r == -1)
		return (-1);
	return (cnt + r);
}
