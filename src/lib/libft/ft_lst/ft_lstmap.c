/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 06:20:50 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 21:02:31 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"
#include <stddef.h>
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_data;

	if (f == NULL || del == NULL)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_data = f(lst->data);
		if (new_data == NULL)
			return (ft_lstclear(&new_list, del), NULL);
		new_node = ft_lstnew(new_data);
		if (!new_node)
		{
			del(new_data);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
