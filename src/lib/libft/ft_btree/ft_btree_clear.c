/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 02:46:28 by teando            #+#    #+#             */
/*   Updated: 2025/01/05 02:46:29 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	ft_btree_clear(t_btree **root, void (*del)(void *))
{
	if (!root || !del || !*root)
		return ;
	ft_btree_clear(&(*root)->left, del);
	ft_btree_clear(&(*root)->right, del);
	del((*root)->item);
	free(*root);
	*root = NULL;
}
