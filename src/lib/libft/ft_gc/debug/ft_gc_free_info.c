/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_free_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:07:11 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 15:32:11 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"
#include "ft_lst.h"

size_t	ft_gc_free_info(const t_list *gc)
{
	return (ft_lstsize((t_list *)gc) - ft_gc_count_data((t_list *)gc));
}
