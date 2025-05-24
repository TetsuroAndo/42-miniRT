/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:28:38 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/24 01:09:43 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"

/* 反射ベクトル (未使用ならコメントアウト可) */
// static inline t_vec3 reflect_vec(t_vec3 v, t_vec3 n)
// {
// 	return (vec3_sub(v, vec3_scale(n, 2.0 * vec3_dot(v, n))));
// }

/**
 * @brief イメージバッファの特定ピクセルに色を設定する関数
 * 
 * @param img イメージ情報を格納した構造体へのポインタ
 * @param x ピクセルのX座標
 * @param y ピクセルのY座標
 * @param color 設定する色値（TRGB形式の32ビット整数）
 * 
 * この関数は、MinilibXのイメージバッファの特定のピクセルに直接色を設定します。
 * バッファ内の正確なメモリ位置を計算し、その位置に色値を書き込みます。
 * メモリ位置は、行の長さ（line_len）とピクセルあたりのビット数（bpp）を考慮して計算されます。
 */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->px + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief シーンをレンダリングしてイメージバッファに描画する関数
 * 
 * @param img 描画先のイメージ情報を格納した構造体へのポインタ
 * @param app アプリケーション全体の状態を保持する構造体へのポインタ
 * 
 * この関数は、レイトレーシングの主要なレンダリングループを実行します。
 * 以下の処理を行います：
 * 1. 画像の全ピクセルに対してループ処理
 * 2. 各ピクセルに対して、カメラからピクセル方向へのレイを生成
 * 3. trace_ray関数を呼び出してレイトレーシングを実行
 * 4. 計算された色をイメージバッファの対応するピクセルに設定
 * 
 * この関数は、レイトレーシングの心臓部であり、シーン内のすべてのオブジェクト、
 * 光源、反射などを考慮したリアルな画像を生成します。
 */
void	render(t_img *img, t_app *app)
{
	int		i;
	int		j;
	int		color_value;
	t_ray	rr;
	t_rgbd	sum;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			rr = (t_ray){.orig = app->scene->cam.pos,
				.dir = get_ray_direction(&app->scene->cam, j, i)};
			sum = trace_ray(rr, app, 0);
			color_value = rgbd_to_trgb(sum);
			my_mlx_pixel_put(img, j, i, color_value);
			j++;
		}
		i++;
	}
}

/**
 * @brief レンダリング環境を初期化し、最初のレンダリングを行う関数
 * 
 * @param app アプリケーション全体の状態を保持する構造体へのポインタ
 * 
 * この関数は、アプリケーションの起動時に呼び出され、以下の処理を行います：
 * 1. MinilibXの初期化（mlx_init）
 * 2. ウィンドウの作成（mlx_new_window）
 * 3. イメージバッファの作成と初期化（mlx_new_image, mlx_get_data_addr）
 * 4. 最初のレンダリングを実行（render関数を呼び出し）
 * 5. レンダリング結果をウィンドウに表示（mlx_put_image_to_window）
 * 
 * 初期化に失敗した場合は、アプリケーションを終了します（exit_app）。
 * この関数は、アプリケーションのグラフィック環境をセットアップし、
 * 最初のレンダリング結果を表示する役割を果たします。
 */
void	init_render(t_app *app)
{
	t_img	*img;

	app->mlx = mlx_init();
	if (!app->mlx)
		exit_app(app, 1);
	app->win = mlx_new_window(app->mlx, WIDTH, HEIGHT, "miniRT");
	if (!app->win)
		exit_app(app, 1);
	img = app->img;
	img->width = WIDTH;
	img->height = HEIGHT;
	img->ptr = mlx_new_image(app->mlx, img->width, img->height);
	if (!img->ptr)
		exit_app(app, 1);
	img->px = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len,
			&img->endian);
	render(img, app);
	mlx_put_image_to_window(app->mlx, app->win, img->ptr, 0, 0);
}

/**
 * @brief MinilibXのループフックで呼び出される再描画関数
 * 
 * @param param アプリケーションデータを格納したポインタ（t_app型にキャストされる）
 * @return int 常に0を返す（MinilibXの規約に従う）
 * 
 * この関数は、MinilibXのループフック（mlx_loop_hook）に登録され、
 * アプリケーションのメインループの各反復で呼び出されます。
 * 
 * 以下の処理を行います：
 * 1. アプリケーションの「汚れ」フラグ（dirty）をチェック
 * 2. フラグが立っていれば（再描画が必要な場合）、フラグをリセット
 * 3. シーンを再レンダリング（render関数を呼び出し）
 * 4. 新しいレンダリング結果をウィンドウに表示
 * 
 * この仕組みにより、シーンに変更があった場合（オブジェクトの移動や追加など）にのみ
 * 再レンダリングが行われ、パフォーマンスが最適化されます。
 */
int	redraw_loop(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (app->dirty == 0)
		return (0);
	app->dirty = 0;
	render(app->img, app);
	mlx_put_image_to_window(app->mlx, app->win, app->img->ptr, 0, 0);
	return (0);
}
