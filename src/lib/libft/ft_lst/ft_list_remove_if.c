/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:30:35 by teando            #+#    #+#             */
/*   Updated: 2024/12/18 17:28:42 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"
#include <stdlib.h>

void	ft_list_remove_if(t_list **begin_list, void *data_ref,
		int (*cmp)(void *, void *), void (*free_fct)(void *))
{
	t_list	*current;
	t_list	*prev;
	t_list	*tmp;

	current = *begin_list;
	prev = 0;
	while (current)
	{
		if ((*cmp)(current->data, data_ref) == 0)
		{
			tmp = current->next;
			(*free_fct)(current->data);
			free(current);
			if (!prev)
				*begin_list = tmp;
			else
				prev->next = tmp;
			current = tmp;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
