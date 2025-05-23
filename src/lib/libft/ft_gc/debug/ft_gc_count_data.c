/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_count_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:06:08 by teando            #+#    #+#             */
/*   Updated: 2025/04/29 20:06:57 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"
#include "ft_lst.h"

size_t	ft_gc_count_data(const t_list *gc)
{
	size_t	count;
	t_list	*cur;

	if (!gc)
		return (0);
	count = 0;
	cur = gc->next;
	while (cur)
	{
		if (cur->data)
			++count;
		cur = cur->next;
	}
	return (count);
}
