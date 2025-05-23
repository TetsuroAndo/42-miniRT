/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_create_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 07:30:47 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 02:46:19 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

t_btree	*ft_btree_create_node(void *item)
{
	t_btree	*node;

	node = (t_btree *)malloc(sizeof(t_btree));
	if (node)
	{
		node->item = item;
		node->left = NULL;
		node->right = NULL;
	}
	return (node);
}

t_btree	*ftx_btree_create_node(void *item, void *sys_info,
		void (*sys_exit)(void *))
{
	t_btree	*node;

	node = ft_btree_create_node(item);
	if (!node)
	{
		sys_exit(sys_info);
	}
	return (node);
}
