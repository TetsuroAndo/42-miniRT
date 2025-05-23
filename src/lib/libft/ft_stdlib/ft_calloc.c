/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:23:06 by teando            #+#    #+#             */
/*   Updated: 2024/11/21 03:15:33 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include <stddef.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	all_size;

	all_size = count * size;
	if (size && all_size / size != count)
		return (NULL);
	if (!count || !size)
		return (malloc(0));
	ptr = malloc(all_size);
	if (ptr)
		ft_bzero(ptr, all_size);
	return (ptr);
}
