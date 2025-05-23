/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 03:51:06 by teando            #+#    #+#             */
/*   Updated: 2024/11/19 00:14:15 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stddef.h>
#include <stdlib.h>

void	*ft_orealloc(void *ptr, size_t oldsize, size_t size)
{
	void	*newptr;

	if (!ptr)
		return (malloc(size));
	if (!size)
		return (free(ptr), NULL);
	newptr = malloc(size);
	if (!newptr)
		return (NULL);
	if (oldsize < size)
		ft_memcpy(newptr, ptr, oldsize);
	else
		ft_memcpy(newptr, ptr, size);
	free(ptr);
	return (newptr);
}
