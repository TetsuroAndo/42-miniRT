/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:53:18 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 10:20:58 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_accel.h"

/* 軸比較ソート用 */
static int	cmp_obj(const void *a, const void *b)
{
	int		axis;
	t_aabb	A;
	t_aabb	B;

	axis = rand() % 3;
	A = obj_bbox(*(t_obj **)a);
	B = obj_bbox(*(t_obj **)b);
	if (((double *)&A.min)[axis]
		+ ((double *)&A.max)[axis] > ((double *)&B.min)[axis]
		+ ((double *)&B.max)[axis])
		return (1);
	return (-1);
}

static t_bvh	*bvh_build(t_obj **list, int n, t_app *app)
{
	t_bvh	*node;
	int		i;
	int		mid;

	node = xcalloc(1, sizeof(*node), app);
	if (n <= 4) /* 葉ノード */
	{
		node->objs = list;
		node->obj_cnt = n;
		if (n > 0)
		{
			node->box = obj_bbox(list[0]);
			i = 1;
			while (i < n)
				node->box = aabb_merge(node->box, obj_bbox(list[i++]));
		}
		return (node);
	}
	ft_qsort(list, n, sizeof(t_obj *), cmp_obj);
	mid = n / 2;
	node->left = bvh_build(list, mid, app);
	node->right = bvh_build(list + mid, n - mid, app);
	if (node->left && node->right)
		node->box = aabb_merge(node->left->box, node->right->box);
	return (node);
}

int	make_bvh(t_scene *scene, t_app *app)
{
	int		n;
	t_obj	**arr;
	int		i;

	n = 0;
	for (t_obj *o = scene->objs; o; o = o->next)
		++n;
	arr = xmalloc(sizeof(t_obj *) * n, app);
	i = 0;
	for (t_obj *o = scene->objs; o; o = o->next)
		arr[i++] = o;
	app->bvh = bvh_build(arr, n, app);
	return (0);
}
