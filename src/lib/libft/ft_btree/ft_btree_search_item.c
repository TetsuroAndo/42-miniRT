/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_search_item.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 07:32:30 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 08:23:15 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	*ft_btree_search_item(t_btree *root, void *data_ref, int (*cmpf)(void *,
			void *))
{
	void	*res;

	if (!root)
		return (0);
	res = ft_btree_search_item(root->left, data_ref, cmpf);
	if (res != 0)
		return (res);
	if (cmpf(data_ref, root->item) == 0)
		return (root->item);
	return (ft_btree_search_item(root->right, data_ref, cmpf));
}
