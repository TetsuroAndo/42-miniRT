/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_by_level.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 07:29:26 by teando            #+#    #+#             */
/*   Updated: 2025/04/29 20:06:34 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include <stdlib.h>

static void	enqueue(t_queue **begin, t_btree *node, int level)
{
	t_queue	*new_elem;
	t_queue	*tmp;

	new_elem = (t_queue *)malloc(sizeof(t_queue));
	if (!new_elem)
		return ;
	new_elem->node = node;
	new_elem->level = level;
	new_elem->next = 0;
	if (!*begin)
		*begin = new_elem;
	else
	{
		tmp = *begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_elem;
	}
}

static t_btree	*dequeue(t_queue **begin, int *level)
{
	t_queue	*tmp;
	t_btree	*node;

	if (!*begin)
		return (0);
	node = (*begin)->node;
	*level = (*begin)->level;
	tmp = *begin;
	*begin = (*begin)->next;
	free(tmp);
	return (node);
}

void	ft_btree_apply_by_level(t_btree *root, void (*applyf)(void *item,
			int current_level, int is_first_elem))
{
	t_queue	*queue;
	t_btree	*node;
	int		level;
	int		prev_level;

	if (!root)
		return ;
	queue = 0;
	enqueue(&queue, root, 0);
	prev_level = -1;
	while (queue)
	{
		node = dequeue(&queue, &level);
		if (level != prev_level)
		{
			applyf(node->item, level, 1);
			prev_level = level;
		}
		else
			applyf(node->item, level, 0);
		if (node->left)
			enqueue(&queue, node->left, level + 1);
		if (node->right)
			enqueue(&queue, node->right, level + 1);
	}
}
