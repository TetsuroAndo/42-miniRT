/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_untrack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:59:17 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 15:00:33 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"
#include <stdlib.h>

int	ft_gc_untrack(t_list *gc, void *p)
{
	t_list	*cur;
	t_list	*prev;

	if (!gc || !p)
		return (-1);
	prev = gc;
	cur = gc->next;
	while (cur)
	{
		if (cur->data == p)
		{
			prev->next = cur->next;
			free(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (-1);
}
