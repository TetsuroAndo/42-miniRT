/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:03:38 by teando            #+#    #+#             */
/*   Updated: 2025/05/04 22:29:57 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "libft.h"
# include "mlx.h"
# include "debug.h"
# include "err.h"
# include "xlib.h"
# include "rt_obj.h"
# include "rt_scene.h"
# include "rt_render.h"
# include "rt_vec.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>

/* MLX + GC + Scene をまとめたグローバルコンテキスト */
typedef struct s_app
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_scene	scene;
	int		fd;  /* 現在オープン中のファイルディスクリプタ */
	t_list	*gc; /* ガベージコレクション用ヘッダノード */
}			t_app;

int			init_app(void);
void		exit_app(t_app *app, int code);
void		exit_errmsg(char *msg, t_app *app);

#endif