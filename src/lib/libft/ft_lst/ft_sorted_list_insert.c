/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_list_insert.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:31:35 by teando            #+#    #+#             */
/*   Updated: 2024/12/18 17:28:49 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

t_list	*ft_create_elem(void *data);

void	ft_sorted_list_insert(t_list **begin_list, void *data,
		int (*cmp)(void *, void *))
{
	t_list	*current;
	t_list	*prev;
	t_list	*new;

	new = ft_create_elem(data);
	if (!new)
		return ;
	if (!*begin_list || (*cmp)((*begin_list)->data, data) > 0)
	{
		new->next = *begin_list;
		*begin_list = new;
		return ;
	}
	prev = 0;
	current = *begin_list;
	while (current && (*cmp)(current->data, data) <= 0)
	{
		prev = current;
		current = current->next;
	}
	prev->next = new;
	new->next = current;
}
