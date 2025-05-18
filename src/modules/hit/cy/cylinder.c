/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:51:37 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/15 17:51:46 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_hit.h"

t_hit_record	cylinder_hit(t_obj *obj, t_ray ray, t_app *app)
{
	t_hit_record	result;
	(void)obj;
	(void)ray;
	(void)app;
	
	result.t = INFINITY;
	
	return (result);
}
