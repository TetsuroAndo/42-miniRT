/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_lights_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:19:28 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/22 20:20:30 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"

/**
 * @brief 拡散反射係数（kd）を計算する関数
 * 
 * @param hit 衝突情報を格納した構造体へのポインタ
 * @param light_dir 衝突点から光源への方向ベクトル（正規化済み）
 * @param atten 光の減衰係数（距離に基づくアテニュエーション）
 * @return double 計算された拡散反射係数
 * 
 * この関数は、Lambertの余弦則に基づいて拡散反射係数を計算します。
 * 法線ベクトルと光の方向ベクトルの内積を求め、負の値は0にクランプします。
 * これに光の減衰係数を掛けて最終的な拡散反射係数を返します。
 * 内積が大きいほど（法線と光の方向が近いほど）、反射は強くなります。
 */
double	calc_kd(const t_hit_record *hit, t_vec3 light_dir, double atten)
{
	const double	diff = fmax(vec3_dot(hit->normal, light_dir), 0.0);

	return (diff * atten);
}

/**
 * @brief 鏡面反射係数（ks）を計算する関数
 * 
 * @param hit 衝突情報を格納した構造体へのポインタ
 * @param light_dir 衝突点から光源への方向ベクトル（正規化済み）
 * @param view_dir 衝突点から視点（カメラ）への方向ベクトル（正規化済み）
 * @param atten 光の減衰係数（距離に基づくアテニュエーション）
 * @return double 計算された鏡面反射係数
 * 
 * この関数は、Blinn-Phong反射モデルに基づいて鏡面反射係数を計算します。
 * 以下の手順で計算を行います：
 * 1. 光の方向ベクトルと視線方向ベクトルの中間ベクトル（ハーフベクトル）を計算
 * 2. 法線ベクトルとハーフベクトルの内積を求め、負の値は0にクランプ
 * 3. 内積をオブジェクトの光沢度（shininess）乗でべき乗
 * 4. 結果に光の減衰係数を掛けて最終的な鏡面反射係数を返す
 * 
 * 光沢度が高いほど、鏡面反射はより難しく、より小さく、より銘々としたものになります。
 */
double	calc_ks(const t_hit_record *hit, t_vec3 light_dir, t_vec3 view_dir,
		double atten)
{
	t_vec3	half_dir;
	double	spec_dot;

	half_dir = vec3_normalize(vec3_add(light_dir, view_dir));
	spec_dot = fmax(vec3_dot(hit->normal, half_dir), 0.0);
	return (pow(spec_dot, hit->obj->shininess) * atten);
}
