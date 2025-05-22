/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:03:38 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 20:54:28 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

/* origin lib */
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
/* マルチスレッド & BVH を廃止したので両方削除 */

/* std lib */
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_img	t_img;
/* typedef も不要 */

/* MLX + GC + Scene をまとめたグローバルコンテキスト */
typedef struct s_app
{
	void				*mlx;
	void				*win;
	int					dirty; /* 再描画が必要な場合: 1, 描画完了: 0 */
	t_scene				*scene;
	t_img				*img;
	/* bvh / renderq は丸ごと撤去 */
	int					fd;
	t_list				*gc;
}						t_app;

t_app					*init_app(void);
void					exit_app(t_app *app, int code);
void					exit_errmsg(char *msg, t_app *app);

/*hook*/
void					setup_hooks(t_app *app);

#endif
