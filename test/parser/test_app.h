#ifndef TEST_APP_H
# define TEST_APP_H

/* テスト環境かどうかを判定するマクロ */
# define TEST_MODE 1

/* 必要なヘッダーのインクルード */
# include <stddef.h>

/* テストに必要な構造体を定義 */
#include "../../inc/rt_obj.h"
#include "../../inc/rt_scene.h"
#include "../../inc/rt_vec.h"
#include "../../inc/rt_render.h"

/* libftのリスト構造体の前方宣言 */
struct s_list;
typedef struct s_list t_list;

/* ─── Unit-Test 用最小 app 構造体 ───────────────────────── */
typedef struct s_app
{
	void    *mlx;       /* ダミー。NULL 固定で OK                                  */
	void    *win;       /* ダミー                                                  */
	t_img    img;       /* 未使用                                                 */
	t_scene  *scene;     /* パーサがここへ書き込む                                 */
	int      fd;        /* xopen / xclose が触る                                  */
	t_list  *gc;        /* ガーベジコレクタ root                                   */
}              t_app;

void print_scene(t_scene *scene);

#endif
