/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:04:47 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 15:32:26 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"
#include "ft_lst.h"

void	ft_gc_clear(t_list *gc)
{
	if (!gc)
		return ;
	ft_gc_free_data(gc);
	ft_gc_free_nodes(gc);
}
