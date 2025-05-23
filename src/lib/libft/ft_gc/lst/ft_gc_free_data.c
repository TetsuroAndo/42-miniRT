/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_free_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:04:42 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 15:05:49 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"
#include <stdlib.h>

void	ft_gc_free_data(t_list *gc)
{
	t_list	*cur;

	if (!gc)
		return ;
	cur = gc->next;
	while (cur)
	{
		if (cur->data)
		{
			free(cur->data);
			cur->data = NULL;
		}
		cur = cur->next;
	}
}
