/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:28:43 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 21:02:15 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

t_list	*ft_list_last(t_list *begin_list)
{
	t_list	*current;

	current = begin_list;
	if (!current)
		return (0);
	while (current->next)
		current = current->next;
	return (current);
}
