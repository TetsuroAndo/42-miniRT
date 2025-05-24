/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:48:53 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/22 19:49:45 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"

/**
 * @brief カメラの基底ベクトルを初期化する関数
 * 
 * @param cam カメラ情報を格納した構造体へのポインタ
 * @return t_cam_basis 初期化されたカメラの基底ベクトル情報
 * 
 * この関数は、カメラの向きからカメラの座標系を构築します。
 * 以下の処理を行います：
 * 1. カメラの前方向ベクトル（forward）を正規化
 * 2. 世界座標の上方向（world_up）を使用して、カメラの右方向ベクトル（right）を計算
 * 3. 前方向と上方向がほぼ平行な場合は、別の世界座標の上方向を選択
 * 4. カメラの上方向ベクトル（up）を計算
 * 5. アスペクト比と視野角（FOV）から、ビューポートの半幅と半高を計算
 * 
 * これにより、カメラの向きに基づいた正規直交基底（オーソノーマル基底）が構築され、
 * ピクセル座標からレイの方向を計算するための基礎が整います。
 */
t_cam_basis	init_cam_basis(t_camera *cam)
{
	t_cam_basis	basis;
	double		aspect;
	double		theta;
	t_vec3		world_up;
	double		dot_product;

	world_up = vec3_new(0, 1, 0);
	basis.forward = vec3_normalize(cam->dir);
	dot_product = fabs(vec3_dot(basis.forward, world_up));
	if (dot_product > 0.9)
	{
		world_up = vec3_new(0, 0, 1);
		if (fabs(vec3_dot(basis.forward, world_up)) > 0.9)
			world_up = vec3_new(1, 0, 0);
	}
	basis.right = vec3_normalize(vec3_cross(basis.forward, world_up));
	basis.up = vec3_cross(basis.right, basis.forward);
	aspect = (double)WIDTH / (double)HEIGHT;
	theta = cam->fov * M_PI / 180.0;
	basis.half_h = tan(theta / 2.0);
	basis.half_w = aspect * basis.half_h;
	return (basis);
}

/**
 * @brief カメラからピクセル座標に向かうレイの方向を計算する関数
 * 
 * @param cam カメラ情報を格納した構造体へのポインタ
 * @param x ピクセルのX座標（0～WIDTH-1）
 * @param y ピクセルのY座標（0～HEIGHT-1）
 * @return t_vec3 計算されたレイの方向ベクトル（正規化済み）
 * 
 * この関数は、レイトレーシングの中核となる処理で、ピクセル座標からレイの方向を計算します。
 * 以下の処理を行います：
 * 1. カメラの基底ベクトルを初期化
 * 2. ピクセル座標を正規化座標（0.0～1.0）に変換
 * 3. 正規化座標をビューポート座標（-half_w～half_w, -half_h～half_h）に変換
 * 4. カメラの基底ベクトルを使用して、ピクセルに向かう方向ベクトルを計算
 * 5. 方向ベクトルを正規化して返す
 * 
 * ピクセルの中心を使用するために、座標に0.5を加算しています。
 * Y座標はスクリーン座標系（上から下）とビューポート座標系（下から上）の
 * 違いを考慮して反転されています。
 */
t_vec3	get_ray_direction(t_camera *cam, int x, int y)
{
	double		u;
	double		v;
	t_vec3		pixel_dir;
	t_cam_basis	basis;

	basis = init_cam_basis(cam);
	u = ((double)x + 0.5) / (double)WIDTH;
	v = ((double)y + 0.5) / (double)HEIGHT;
	u = (2.0 * u - 1.0) * basis.half_w;
	v = (1.0 - 2.0 * v) * basis.half_h;
	pixel_dir = vec3_add(basis.forward, vec3_add(vec3_scale(basis.right, u),
				vec3_scale(basis.up, v)));
	return (vec3_normalize(pixel_dir));
}

/**
 * @brief カメラからサブピクセル座標に向かうレイの方向を計算する関数
 * 
 * @param cam カメラ情報を格納した構造体へのポインタ
 * @param x サブピクセルのX座標（浮動小数点数）
 * @param y サブピクセルのY座標（浮動小数点数）
 * @return t_vec3 計算されたレイの方向ベクトル（正規化済み）
 * 
 * この関数は、get_ray_direction関数の作業を浮動小数点数のサブピクセル座標で行います。
 * アンチエイリアシング（ジャギー軽減）やモーションブラーなどの高度なレンダリング技術で
 * 使用される可能性があります。
 * 
 * 処理の流れはget_ray_direction関数と同様ですが、入力が整数ではなく浮動小数点数である点が
 * 異なります。これにより、ピクセル内の任意の位置からレイを発射することが可能になります。
 */
t_vec3	get_ray_dir_sub(t_camera *cam, double x, double y)
{
	t_cam_basis	b;
	double		u;
	double		v;

	b = init_cam_basis(cam);
	u = (x + 0.5) / (double)WIDTH;
	v = (y + 0.5) / (double)HEIGHT;
	u = (2.0 * u - 1.0) * b.half_w;
	v = (1.0 - 2.0 * v) * b.half_h;
	return (vec3_normalize(vec3_add(b.forward, vec3_add(vec3_scale(b.right, u),
					vec3_scale(b.up, v)))));
}
