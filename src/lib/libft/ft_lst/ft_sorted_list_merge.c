/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_list_merge.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:31:35 by teando            #+#    #+#             */
/*   Updated: 2024/12/18 17:28:54 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

static void	insert_in_sorted(t_list **begin_list, t_list *node,
		int (*cmp)(void *, void *))
{
	t_list	*current;
	t_list	*prev;

	if (!*begin_list || (*cmp)((*begin_list)->data, node->data) > 0)
	{
		node->next = *begin_list;
		*begin_list = node;
		return ;
	}
	prev = 0;
	current = *begin_list;
	while (current && (*cmp)(current->data, node->data) <= 0)
	{
		prev = current;
		current = current->next;
	}
	prev->next = node;
	node->next = current;
}

void	ft_sorted_list_merge(t_list **begin_list1, t_list *begin_list2,
		int (*cmp)())
{
	t_list	*next_node;

	while (begin_list2)
	{
		next_node = begin_list2->next;
		insert_in_sorted(begin_list1, begin_list2, cmp);
		begin_list2 = next_node;
	}
}
