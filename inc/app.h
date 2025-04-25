/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:03:38 by teando            #+#    #+#             */
/*   Updated: 2025/04/25 16:54:59 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "libft.h"
# include "mlx.h"
# include "debug.h"
# include "err.h"
# include "xlib.h"
# include "rt_obj.h"

/* MLX + GC + Scene をまとめたグローバルコンテキスト */
typedef struct s_app
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_scene	scene;
	t_list	*gc; /* ガベージコレクション用ヘッダノード */
}			t_app;

int			init_app(void);
void		exit_app(t_app *app, int code);

#endif