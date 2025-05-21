/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:59:36 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 10:20:49 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_accel.h"
#include "rt_render.h"

/* 再帰ヒット */
int	bvh_hit(t_bvh *node, t_ray r, double t_max, t_hit_record *out)
{
	int				hit_any;
	int				i;
	t_hit_record	tmp;

	if (!aabb_hit(node->box, r, t_max))
		return (0);
	hit_any = 0;
	if (node->left || node->right)
	{
		if (node->left && bvh_hit(node->left, r, t_max, out))
		{
			t_max = out->t;
			hit_any = 1;
		}
		if (node->right && bvh_hit(node->right, r, t_max, out))
		{
			t_max = out->t;
			hit_any = 1;
		}
	}
	else
	{
		for (i = 0; i < node->obj_cnt; ++i)
		{
			tmp = node->objs[i]->hit(node->objs[i], r, NULL);
			if (tmp.t > 0 && tmp.t < t_max)
			{
				*out = tmp;
				t_max = tmp.t;
				hit_any = 1;
			}
		}
	}
	return (hit_any);
}
