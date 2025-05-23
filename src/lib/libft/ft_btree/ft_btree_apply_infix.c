/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_infix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 07:29:53 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 08:22:56 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	ft_btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (!root)
		return ;
	ft_btree_apply_infix(root->left, applyf);
	applyf(root->item);
	ft_btree_apply_infix(root->right, applyf);
}
