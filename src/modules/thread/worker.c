/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:17:06 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 12:30:54 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_thread.h"
#include "mod_render.h"

/* ------ 内部 forward ------ */
static void *worker_main(void *arg);
static int   fetch_tile(t_renderq *q);

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

/* ------ 外部 API  ------ */
void spawn_workers(t_app *app, t_renderq *q, int nthreads)
{
	app->workers = xmalloc(sizeof(pthread_t) * nthreads, app);
	app->n_workers = nthreads;
	app->renderq = q;
	for (int i = 0; i < nthreads; ++i)
		pthread_create(&app->workers[i], NULL, worker_main, (void *)app);
	app->workers_ready = 1;
}

/* ------ ワーカ本体 ------ */
static void *worker_main(void *arg)
{
	t_app *app = (t_app *)arg;
	t_renderq *q = app->renderq;

	while (1)
	{
		/* --- ① フレーム/目標 SPP をローカル変数へコピー --- */
		pthread_mutex_lock(&app->rstate.lock);
		int my_frame   = app->rstate.task_id;
		int spp_goal   = app->rstate.spp_target;
		pthread_mutex_unlock(&app->rstate.lock);

		/* --- ② タイル処理ループ --- */
		int id;
		while ((id = fetch_tile(q)) >= 0)
		{
			t_tile t = q->tiles[id];
			for (int y = t.y0; y < t.y1; ++y)
				for (int x = t.x0; x < t.x1; ++x)
				{
					const double ofs[5][2] = {{0.5,0.5},{0.25,0.25},{0.75,0.25},{0.25,0.75},{0.75,0.75}};
					t_rgbd sum = {0,0,0};
					for (int s=0; s<spp_goal; ++s)
					{
						t_ray rr = {.orig = app->scene->cam.pos,
									.dir  = get_ray_dir_sub(&app->scene->cam,
													x+ofs[s][0], y+ofs[s][1])};
						sum = rgbd_add(sum, trace_ray(rr, app, 0));
					}
					sum = rgbd_scale(sum, 1.0 / (double)spp_goal);
					my_mlx_pixel_put(app->img, x, y, rgbd_to_trgb(sum));
				}
		}

		/* --- ③ タイル処理完了: さらに SPP を増やすか、次フレーム待機 --- */
		pthread_mutex_lock(&app->rstate.lock);
		if (my_frame == app->rstate.task_id)      /* 同フレームか確認 */
		{
			if (spp_goal < SPP)                   /* まだ最大 SPP 未達 */
			{
				app->rstate.spp_target = spp_goal << 1;
				reset_tile_queue(q);
				pthread_cond_broadcast(&app->rstate.cv);
				pthread_mutex_unlock(&app->rstate.lock);
				continue;                         /* 次ループで再レンダ */
			}
			else                                  /* 最大 SPP 完了 */
			{
				apply_fxaa(app->img);             /* 最終パスで FXAA */
				mlx_put_image_to_window(app->mlx, app->win, app->img->ptr, 0, 0);
			}
		}

		/* 待機: task_id が更新されるまで cond_wait */
		while (my_frame == app->rstate.task_id)
			pthread_cond_wait(&app->rstate.cv, &app->rstate.lock);
		pthread_mutex_unlock(&app->rstate.lock);
	}
	return (NULL);
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
