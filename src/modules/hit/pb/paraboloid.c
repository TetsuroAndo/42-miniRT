/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:50:52 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/21 13:50:49 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_hit.h"

t_hit_record	paraboloid_hit(t_obj *obj, t_ray ray, t_app *app)
{
	t_hit_record	result;
	(void)obj;
	(void)ray;
	(void)app;

	result.t = -1.0;

	return (result);
}
