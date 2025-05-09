// #ifndef TEST_APP_H
// # define TEST_APP_H

// # include <stdlib.h>
// # include <stdint.h>
// # include <stdio.h>
// # include <fcntl.h>
// # include <unistd.h>
// # include "libft.h"
// # include "../../inc/err.h"
// # include "../../inc/rt_scene.h"
// # include "../../inc/rt_obj.h"
// # include "../../inc/rt_vec.h"
// # include "../../inc/rt_render.h"

// /* アプリケーション構造体 */
// typedef struct s_app
// {
// 	void	*mlx;
// 	void	*win;
// 	t_img	img;
// 	t_scene	scene;
// 	int		fd;
// 	t_list	*gc;
// }			t_app;
// /* init app */
// t_app *init_app(void);

// /* finalize app */
// void exit_app(t_app *app, int code);

// /* エラー終了関数のモック */
// void    exit_errmsg(char *msg, t_app *app);

// #endif
