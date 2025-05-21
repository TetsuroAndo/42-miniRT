/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:03:38 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 10:24:33 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

/* origin lib */
# include "debug.h"
# include "err.h"
# include "libft.h"
# include "mlx.h"
# include "xlib.h"

/* rt */
# include "rt_render.h"
# include "rt_scene.h"

/* modules */
# include "mod_hit.h"
# include "mod_parse.h"
# include "mod_render.h"
# include "mod_thread.h"
# include "mod_accel.h"

/* std lib */
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_bvh		t_bvh;
typedef struct s_img		t_img;
typedef struct s_renderq	t_renderq;

/* ── プログレッシブ描画共有状態 ── */
typedef struct s_render_state
{
    volatile int     task_id;      /* dirty ごとに ++           */
    volatile int     spp_target;   /* 1→2→4→…→FINAL_SPP        */
    pthread_mutex_t  lock;
    pthread_cond_t   cv;
}               t_render_state;

/* MLX + GC + Scene をまとめたグローバルコンテキスト */
typedef struct s_app
{
	void		*mlx;
	void		*win;
	int			dirty;		/* 再描画が必要な場合: 1, 描画完了: 0 */
	t_scene		*scene;
	t_bvh		*bvh;
	t_img		*img;
	t_renderq	*renderq;

    /* --- 常駐ワーカープール --- */
    t_render_state rstate;
    pthread_t  *workers;
    int         n_workers;
    int         workers_ready;
	int			fd;
	t_list		*gc;
}			t_app;


t_app		*init_app(void);
void		exit_app(t_app *app, int code);
void		exit_errmsg(char *msg, t_app *app);

/*hook*/
void	setup_hooks(t_app *app);

#endif
