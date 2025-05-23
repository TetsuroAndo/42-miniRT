/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 05:32:00 by teando            #+#    #+#             */
/*   Updated: 2025/05/24 01:14:11 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_cam.h"
#include "xlib.h"
#include <math.h>

void	cam_translate(t_camera *cam, t_vec3 delta)
{
	cam->pos = vec3_add(cam->pos, delta);
}

void	cam_rotate_yaw(t_camera *cam, double rad)
{
	cam->dir = vec3_rotate(cam->dir, (t_vec3){0, 1, 0}, rad);
}

/**
 * @brief カメラのピッチ角（垂直方向の回転）を変更する関数
 * 
 * @param cam 回転させるカメラ情報を格納した構造体へのポインタ
 * @param rad 回転角（ラジアン単位）。正の値は上向き、負の値は下向き
 * 
 * この関数は、カメラの向き（cam->dir）をカメラの右方向を軸として回転させます。
 * 以下の手順で処理を行います：
 * 1. カメラの方向ベクトルと世界座標系のY軸（上方向）の外積を計算して右方向ベクトルを求める
 * 2. 右方向ベクトルを正規化して単位ベクトルにする
 * 3. vec3_rotate関数を使用して、カメラの方向ベクトルを右方向ベクトル周りにrad角度だけ回転させる
 */
void	cam_rotate_pitch(t_camera *cam, double rad)
{
	t_vec3	right;

	right = vec3_normalize(vec3_cross(cam->dir, (t_vec3){0, 1, 0}));
	cam->dir = vec3_rotate(cam->dir, right, rad);
}
