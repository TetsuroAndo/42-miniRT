#ifndef TEST_APP_H
# define TEST_APP_H

# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "../../inc/err.h"
# include "../../inc/rt_scene.h"
# include "../../inc/rt_obj.h"
# include "../../inc/rt_vec.h"
# include "../../inc/rt_render.h"

/* テスト用の簡略化されたアプリケーション構造体 */
typedef struct s_app
{
    t_scene     *scene;
    t_list      *gc;
    int         fd;
}   t_app;

/* init app */
int init_app(t_app *app);

/* finalize app */
void exit_app(t_app *app, int code);

/* エラー終了関数のモック */
void    exit_errmsg(char *msg, t_app *app);

#endif
