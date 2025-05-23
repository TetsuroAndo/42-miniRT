/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_from_strs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:29:42 by teando            #+#    #+#             */
/*   Updated: 2024/12/18 17:28:36 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lst.h"
#include "ft_string.h"
#include <stdlib.h>

t_list	*ft_list_from_strs(char **strs)
{
	t_list	*list;
	t_list	*new;
	char	*dup_str;

	if (!strs || !*strs)
		return (NULL);
	list = NULL;
	while (*strs)
	{
		dup_str = ft_strdup(*strs);
		if (!dup_str)
			return (ft_lstclear(&list, free), NULL);
		new = ft_create_elem(dup_str);
		if (!new)
		{
			free(dup_str);
			ft_lstclear(&list, free);
			return (NULL);
		}
		ft_lstadd_back(&list, new);
		strs++;
	}
	return (list);
}
