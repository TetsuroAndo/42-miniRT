/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:03:38 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 22:57:02 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "err.h"
# include "libft.h"
# include "mlx.h"
# include "mod_hit.h"
# include "mod_parse.h"
# include "mod_render.h"
# include "rt_render.h"
# include "rt_scene.h"
# include "xlib.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_img	t_img;

typedef struct s_app
{
	void				*mlx;
	void				*win;
	int					dirty;
	t_scene				*scene;
	t_img				*img;
	int					fd;
	t_list				*gc;
}						t_app;

t_app					*init_app(void);
void					exit_app(t_app *app, int code);
void					exit_errmsg(char *msg, int lnum, t_app *app);

void					setup_hooks(t_app *app);

#endif
