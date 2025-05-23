/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_level_count.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 07:32:40 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 08:23:13 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

int	ft_btree_level_count(t_btree *root)
{
	int	left_count;
	int	right_count;

	if (!root)
		return (0);
	left_count = ft_btree_level_count(root->left);
	right_count = ft_btree_level_count(root->right);
	if (left_count > right_count)
		return (left_count + 1);
	else
		return (right_count + 1);
}
