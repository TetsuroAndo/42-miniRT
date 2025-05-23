/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_track.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:58:44 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 17:44:20 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"

int	ft_gc_track(t_list *gc, void *p)
{
	t_list	*new;

	if (!gc || !p)
		return (-1);
	new = ft_lstnew(p);
	if (!new)
		return (-1);
	ft_lstadd_front(&gc->next, new);
	return (0);
}
