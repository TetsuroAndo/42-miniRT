/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:04:45 by teando            #+#    #+#             */
/*   Updated: 2025/04/23 15:32:44 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"
#include "ft_lst.h"
#include <stdlib.h>

void	ft_gc_destroy(t_list **gc)
{
	if (!gc || !*gc)
		return ;
	ft_gc_clear(*gc);
	free(*gc);
	*gc = NULL;
}
