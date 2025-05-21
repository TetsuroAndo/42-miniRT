/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_thread.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:13:46 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 13:39:13 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_THREAD_H
# define MOD_THREAD_H

# include "rt_render.h"
# include "xlib.h"
# include <pthread.h>

/* Forward declarations */
typedef struct s_app	t_app;
typedef struct s_img	t_img;

/* タイル構造体 - 変更なし */
typedef struct s_tile /* (x0,x1) × (y0,y1) 半開区間 */
{
	int x0;
	int y0;
	int x1;
	int y1;
}						t_tile;

/* レンダリングキュー＋状態を統合した構造体 */
typedef struct s_render_queue
{
	/* タイル管理 */
	t_tile				*tiles;        /* 長さ tile_cnt の配列 */
	int					tile_cnt;      /* 全タイル数 */
	volatile int		next;          /* fetch-and-add 用 */

	/* レンダリング状態 */
	volatile int		task_id;       /* dirty ごとに ++ */
	volatile int		spp_target;    /* 1→2→4→…→FINAL_SPP */

	/* 同期プリミティブ */
	pthread_mutex_t		lock;          /* 共有データ保護用ロック */
	pthread_cond_t		cv;            /* 条件変数 */
}						t_render_queue;

/* スレッドプール構造体 */
typedef struct s_thread_pool
{
	t_render_queue		queue;         /* レンダリングキュー＋状態（埋め込み） */
	pthread_t			*workers;      /* ワーカースレッド配列 */
	int					n_workers;     /* ワーカー数 */
	int					workers_ready; /* ワーカー準備状態 */
}						t_thread_pool;

/* spawn */
void					spawn_workers(t_app *app, t_renderq *q, int nthreads);

/* worker */
static void				*worker_main(void *arg);

/* tile */
t_renderq				*make_tiles(t_app *app __attribute__((unused)),
							int tile_px);
void					reset_tile_queue(t_renderq *q);

/* destroy */
void					destroy_workers(t_app *app);
void					destroy_tiles(t_renderq *q);

#endif
