/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:29:28 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 13:29:43 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_thread.h"
#include "mod_render.h"

/* ★ 追加: タイルキューを再利用するためのリセット関数 */
void reset_tile_queue(t_renderq *q)
{
	pthread_mutex_lock(&q->lock);
	q->next = 0;
	pthread_mutex_unlock(&q->lock);
}

/* ------ タイル分割ユーティリティ ------ */
t_renderq *make_tiles(t_app *app __attribute__((unused)), int tile_px)
{
	const int w = WIDTH, h = HEIGHT;
	const int nx = (w + tile_px - 1) / tile_px;
	const int ny = (h + tile_px - 1) / tile_px;

	t_renderq *q = xmalloc(sizeof(*q), app);
	q->tile_cnt = nx * ny;
	q->tiles = xmalloc(sizeof(t_tile) * q->tile_cnt, app);
	q->next  = 0;
	pthread_mutex_init(&q->lock, NULL);

	int id = 0;
	for (int ty = 0; ty < ny; ++ty)
		for (int tx = 0; tx < nx; ++tx)
		{
			q->tiles[id++] = (t_tile){
				.x0 = tx * tile_px,
				.y0 = ty * tile_px,
				.x1 = (tx + 1) * tile_px > w ? w : (tx + 1) * tile_px,
				.y1 = (ty + 1) * tile_px > h ? h : (ty + 1) * tile_px};
		}
	return q;
}
