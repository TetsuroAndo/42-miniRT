/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_dump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:06:48 by teando            #+#    #+#             */
/*   Updated: 2025/04/29 20:07:00 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"
#include "ft_stdio.h"
#include <stdint.h>
#include <unistd.h>

static int	put_hex_fd(uintptr_t n, int fd)
{
	const char	hex[17] = "0123456789abcdef";
	char		buf[sizeof(uintptr_t) * 2 + 1];
	int			i;
	ssize_t		ret;

	i = 0;
	if (n == 0)
	{
		if (write(fd, "0", 1) < 0)
			return (-1);
		return (0);
	}
	while (n && i < (int)(sizeof(buf) - 1))
	{
		buf[i++] = hex[n % 16];
		n /= 16;
	}
	while (i--)
	{
		ret = write(fd, &buf[i], 1);
		if (ret < 0)
			return (-1);
	}
	return (0);
}

void	ft_gc_dump(const t_list *gc, int fd)
{
	size_t	idx;
	t_list	*cur;

	idx = 0;
	if (!gc)
	{
		if (write(fd, "(gc=NULL)\n", 10) < 0)
			return ;
		return ;
	}
	cur = gc->next;
	while (cur)
	{
		if (write(fd, "[", 1) < 0 || put_hex_fd(idx++, fd) < 0 || write(fd,
				"] node=0x", 9) < 0 || put_hex_fd((uintptr_t)cur, fd) < 0
			|| write(fd, " data=0x", 8) < 0 || put_hex_fd((uintptr_t)cur->data,
				fd) < 0 || write(fd, "\n", 1) < 0)
			return ;
		cur = cur->next;
	}
}
