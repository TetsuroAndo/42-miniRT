/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:51:16 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/15 17:51:25 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_hit.h"

t_hit_record	hyperboloid_hit(t_obj *obj, t_ray ray, t_app *app)
{
	t_hit_record	result;
	(void)obj;
	(void)ray;
	(void)app;
	
	result.t = INFINITY;
	
	return (result);
}
