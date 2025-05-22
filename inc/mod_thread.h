/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_thread.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:13:46 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 10:23:05 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_THREAD_H
# define MOD_THREAD_H

# include <pthread.h>
# include "rt_render.h"
# include "xlib.h"

/* Forward declarations */
typedef struct s_app t_app;
typedef struct s_img t_img;

typedef struct s_tile
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;	/* (x0,x1) × (y0,y1) 半開区間 */
}	t_tile;

/* スレッド共有データ */
typedef struct s_renderq
{
	t_tile			*tiles;		/* 長さ tile_cnt の配列              */
	int				tile_cnt;	/* 全タイル数                        */
	volatile int	next;		/* fetch-and-add 用                  */
	pthread_mutex_t	lock;		/* タイル配列解放までの生存確保 */
}	t_renderq;

void spawn_workers(t_app *app, t_renderq *q, int nthreads);
t_renderq *make_tiles(t_app *app __attribute__((unused)), int tile_px);

#endif
