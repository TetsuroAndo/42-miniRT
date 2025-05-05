/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:50:00 by teando            #+#    #+#             */
/*   Updated: 2025/05/05 10:17:09 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"
#include <stdlib.h>

int	expect_line_end(char **s)
{
	/* 空行または行末を期待 */
	if (!*s)
		return (1);
	while (**s && ft_isspace(**s))
		(*s)++;
	return (**s == '\0');
}

void	add_obj(t_obj **obj, t_obj *new)
{
	new->next = *obj;
	*obj = new;
}
