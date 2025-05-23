/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_calloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:57:12 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 15:31:50 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"
#include "ft_stdlib.h"
#include <stdlib.h>

void	*ft_gc_calloc(t_list *gc, size_t count, size_t size)
{
	void	*p;

	if (!gc || !count || !size)
		return (NULL);
	p = ft_calloc(count, size);
	if (!p)
		return (NULL);
	if (ft_gc_track(gc, p) < 0)
	{
		free(p);
		return (NULL);
	}
	return (p);
}
