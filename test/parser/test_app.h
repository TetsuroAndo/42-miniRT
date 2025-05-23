#ifndef TEST_APP_H
# define TEST_APP_H

/* テスト環境かどうかを判定するマクロ */
# define TEST_MODE 1

/* 必要なヘッダーのインクルード */
# include <stddef.h>

/* libftのリスト構造体の前方宣言 */
struct s_list;
typedef struct s_list t_list;

/* 前方宣言 */
struct s_scene;
typedef struct s_scene t_scene;
struct s_obj;
typedef struct s_obj t_obj;

/* テスト用の画像バッファ構造体の前方宣言 */
/* 実際の定義はrt_render.hにあるものを使用 */
struct s_img;
typedef struct s_img t_img;

/* ─── Unit-Test 用最小 app 構造体 ───────────────────────── */
typedef struct s_app
{
	void    *mlx;       /* ダミー。NULL 固定で OK                                  */
	void    *win;       /* ダミー                                                  */
	t_img    *img;      /* 未使用                                                 */
	t_scene  *scene;    /* パーサがここへ書き込む                                 */
	int      fd;        /* xopen / xclose が触る                                  */
	t_list   *gc;       /* ガーベジコレクタ root                                   */
}              t_app;

void print_scene(t_scene *scene);    /* 宣言だけ残す */

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

/* 必要最小限の関数プロトタイプ宣言 */
t_list	*xgc_init(t_app *app);
void	*xmalloc(size_t size, t_app *app);
void	*xcalloc(size_t count, size_t size, t_app *app);
void	xfree(void **ptr, t_app *app);
int		xopen(char *filename, int flags, t_app *app);
int		xclose(int *fd);

/* エラー処理関数 */
void	exit_app(t_app *app, int exit_code);
void	exit_errmsg(char *msg, int lnum, t_app *app);
void	set_error(t_app *app, int err_code, const char *msg);

#endif
