/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:49:53 by teando            #+#    #+#             */
/*   Updated: 2024/10/23 20:32:19 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (n--)
		*ptr++ = (unsigned char)c;
	return (b);
}
