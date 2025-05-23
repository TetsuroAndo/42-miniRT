/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oreallocf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 04:01:07 by teando            #+#    #+#             */
/*   Updated: 2024/11/19 00:15:30 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include <stdlib.h>

void	*ft_oreallocf(void *ptr, size_t oldsize, size_t size)
{
	void	*new_ptr;

	new_ptr = ft_orealloc(ptr, oldsize, size);
	if (!new_ptr && ptr)
		free(ptr);
	return (new_ptr);
}
