/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:03:38 by teando            #+#    #+#             */
/*   Updated: 2025/05/08 14:32:17 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "debug.h"
# include "err.h"
# include "libft.h"
# include "mlx.h"
# include "rt_obj.h"
# include "rt_render.h"
# include "rt_scene.h"
# include "rt_vec.h"
# include "xlib.h"
# include "mod_parse.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_img	t_img;

/* MLX + GC + Scene をまとめたグローバルコンテキスト */
typedef struct s_app
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_scene	*scene;
	int		fd;
	t_list	*gc;
}			t_app;


t_app		*init_app(void);
void		exit_app(t_app *app, int code);
void		exit_errmsg(char *msg, t_app *app);

/*hook*/
void	setup_hooks(t_app *app);

#endif