/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_suffix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 07:30:56 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 08:23:08 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	ft_btree_apply_suffix(t_btree *root, void (*applyf)(void *))
{
	if (!root)
		return ;
	ft_btree_apply_suffix(root->left, applyf);
	ft_btree_apply_suffix(root->right, applyf);
	applyf(root->item);
}
