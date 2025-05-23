/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 06:20:32 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 21:02:30 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"
#include <stddef.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (f)
	{
		while (lst != NULL)
		{
			f(lst->data);
			lst = lst->next;
		}
	}
}
