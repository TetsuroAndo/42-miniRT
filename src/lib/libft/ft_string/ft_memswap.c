/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:14:25 by teando            #+#    #+#             */
/*   Updated: 2024/11/13 12:21:58 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_memswap(void *m1, void *m2, size_t n)
{
	unsigned char	temp;
	size_t			i;

	i = 0;
	while (i < n)
	{
		temp = ((unsigned char *)m1)[i];
		((unsigned char *)m1)[i] = ((unsigned char *)m2)[i];
		((unsigned char *)m2)[i] = temp;
		i++;
	}
}
