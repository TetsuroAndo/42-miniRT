/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:58:00 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 14:58:36 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"
#include <stdlib.h>

void	*ft_gc_malloc(t_list *gc, size_t size)
{
	void	*p;

	if (!gc || !size)
		return (NULL);
	p = malloc(size);
	if (!p)
		return (NULL);
	if (ft_gc_track(gc, p) < 0)
	{
		free(p);
		return (NULL);
	}
	return (p);
}
