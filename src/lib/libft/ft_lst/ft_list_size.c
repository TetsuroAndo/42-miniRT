/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:28:43 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 21:02:26 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

int	ft_list_size(t_list *begin_list)
{
	int		count;
	t_list	*current;

	count = 0;
	current = begin_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
