/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:23:19 by teando            #+#    #+#             */
/*   Updated: 2024/12/17 21:18:00 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_strs_clear(void *ptr)
{
	char	**array;
	size_t	i;

	i = 0;
	array = (char **)ptr;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}
