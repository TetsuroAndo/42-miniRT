/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 06:09:45 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 23:25:50 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"
#include <stddef.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	new->next = NULL;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}
