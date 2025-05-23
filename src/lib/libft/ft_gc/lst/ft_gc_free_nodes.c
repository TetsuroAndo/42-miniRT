/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_free_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:04:29 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 15:05:40 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"
#include <stdlib.h>

void	ft_gc_free_nodes(t_list *gc)
{
	t_list	*cur;
	t_list	*next;

	if (!gc)
		return ;
	cur = gc->next;
	gc->next = NULL;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}
