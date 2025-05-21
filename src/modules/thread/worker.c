/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:17:06 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 10:26:03 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_thread.h"

/* Forward declarations */
t_hit_record intersect_ray(t_ray ray, t_app *app, double t_max);
int calculate_light_color(t_hit_record *hit, t_app *app);
void my_mlx_pixel_put(t_img *img, int x, int y, int color);
t_vec3 get_ray_direction(t_camera *cam, int x, int y);

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
				t_ray ray = {
					.orig = app->scene->cam.pos,
					.dir  = get_ray_direction(&app->scene->cam, x, y)};
				t_hit_record h = intersect_ray(ray, app, INFINITY);
				const int c = (h.t > 0 && h.obj)
					? calculate_light_color(&h, app)
					: create_trgb(0, 20, 20, 20);
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
