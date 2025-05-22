#ifndef TEST_APP_H
# define TEST_APP_H

/* テスト環境かどうかを判定するマクロ */
# define TEST_MODE 1

/* 必要なヘッダーのインクルード */
# include <stddef.h>

/* libftのリスト構造体の前方宣言 */
struct s_list;
typedef struct s_list t_list;

struct s_scene;
typedef struct s_scene t_scene;
struct s_obj;
typedef struct s_obj t_obj;

struct s_img;
typedef struct s_img t_img;

typedef struct s_app
{
	void    *mlx;
	void    *win;
	t_img    *img;
	t_scene  *scene;
	int      fd;
	t_list   *gc;
}              t_app;

void print_scene(t_scene *scene);

# include "err.h"
# include "libft.h"
# include "rt_obj.h"
# include "rt_scene.h"
# include "rt_vec.h"
# include "mod_hit.h"
# include "rt_render.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

t_list	*xgc_init(t_app *app);
void	*xmalloc(size_t size, t_app *app);
void	*xcalloc(size_t count, size_t size, t_app *app);
void	xfree(void **ptr, t_app *app);
int		xopen(char *filename, int flags, t_app *app);
int		xclose(int fd);

void	exit_app(t_app *app, int exit_code);
void	exit_errmsg(char *msg, t_app *app);
void	set_error(t_app *app, int err_code, const char *msg);

#endif
