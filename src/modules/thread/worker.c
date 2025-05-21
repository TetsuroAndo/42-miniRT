/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:17:06 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 11:46:54 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_thread.h"
#include "mod_render.h"

/* ------ 内部 forward ------ */
static void *worker_main(void *arg);
static int   fetch_tile(t_renderq *q);

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

/* ------ 外部 API  ------ */
void spawn_workers(t_app *app, t_renderq *q, int nthreads)
{
	pthread_t *tid = xmalloc(sizeof(pthread_t) * nthreads, app);

	for (int i = 0; i < nthreads; ++i)
		pthread_create(&tid[i], NULL, worker_main, (void *)app);

	/* メインスレッドも働く */
	worker_main((void *)app);

	/* 合流 */
	for (int i = 0; i < nthreads; ++i)
		pthread_join(tid[i], NULL);
	pthread_mutex_destroy(&q->lock);
}

/* ------ ワーカ本体 ------ */
static void *worker_main(void *arg)
{
	t_app *app = (t_app *)arg;
	t_renderq *q = (t_renderq *)app->renderq;          /* render.c で埋める */

	int id;
	while ((id = fetch_tile(q)) >= 0)
	{
		t_tile t = q->tiles[id];
		for (int y = t.y0; y < t.y1; ++y)
			for (int x = t.x0; x < t.x1; ++x)
			{
				/* ---- SSAA ×SPP ---- */
				/* サンプル位置の配列をSPPの最大値（4）に合わせて定義 */
				const double ofs[][2] = {
					{0.5,0.5},           /* SPP=1 用の中心位置 */
					{0.25,0.25},          /* SPP=2,4 用の左上 */
					{0.75,0.25},          /* SPP=2,4 用の右上 */
					{0.25,0.75},          /* SPP=4 用の左下 */
					{0.75,0.75}           /* SPP=4 用の右下 */
				};
				t_rgbd sum = {0,0,0};
				for (int s=0;s<SPP;++s)
				{
					t_ray rr = {
						.orig = app->scene->cam.pos,
						.dir  = get_ray_dir_sub(&app->scene->cam,
										x+ofs[s][0], y+ofs[s][1])};
					sum = rgbd_add(sum, trace_ray(rr, app, 0));
				}
				sum = rgbd_scale(sum, 1.0 / (double)SPP);  /* 平均 */
				const int c = rgbd_to_trgb(sum);
				my_mlx_pixel_put(app->img, x, y, c);
			}
	}
	return NULL;
}

/* タイルを 1 枚取得（アトミック）*/
static int fetch_tile(t_renderq *q)
{
	int id;
	/* very light cas で良いが、可搬性優先で mutex */
	pthread_mutex_lock(&q->lock);
	id = q->next < q->tile_cnt ? q->next++ : -1;
	pthread_mutex_unlock(&q->lock);
	return id;
}
