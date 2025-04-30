/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:22:19 by tomsato           #+#    #+#             */
/*   Updated: 2025/04/30 19:27:35 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"
#include "rt_vec.h"
#include "rt_obj.h"
#include <fcntl.h>



t_obj	parse_obj(char *filename, t_app *app)
{
	t_obj	obj;
	int		file_fd;

	obj = NULL;
	file_fd = open(filename, R_OK);
	return (obj);
}