/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:48:06 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 20:49:14 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_hit.h"

void					cy_set_record(t_hit_record *rec, t_obj *obj, t_vec3 pos,
							double t);
void					cy_apply_face_orientation(t_hit_record *rec, t_ray ray);

/**
 * @brief 交差点が円柱のキャップ（底面）の半径内にあるかチェックする関数
 * 
 * @param hit 交差点の位置ベクトル
 * @param center キャップ（底面）の中心位置ベクトル
 * @param r 円柱の半径
 * @return int 交差点が半径内にあれば1、なければ0
 * 
 * この関数は、円柱のキャップ（底面）とレイの交差点が、キャップの半径内にあるかどうかを
 * チェックします。具体的には、交差点からキャップの中心までの距離を計算し、
 * その距離が円柱の半径以下（計算誤差を考慮して少し余裕を持たせる）かどうかをチェックします。
 * 
 * 計算誤差を考慮して、半径にEPSILONの10倍を加えた値を使用しています。
 */
static inline int	cy_cap_valid(t_vec3 hit, t_vec3 center, double r)
{
	return (vec3_len(vec3_sub(hit, center)) <= r + EPSILON * 10);
}

/**
 * @brief 円柱のキャップ（底面）とレイの交差距離を計算する関数
 * 
 * @param ray 交差判定に使用するレイ
 * @param center キャップ（底面）の中心位置ベクトル
 * @param axis 円柱の軸方向ベクトル（正規化済み）
 * @return double レイの原点からキャップとの交差点までの距離、交差がない場合は-1.0
 * 
 * この関数は、円柱のキャップ（底面）とレイの交差距離を計算します。
 * キャップは軸方向に垂直な平面として考えられます。
 * 具体的には、以下の処理を行います：
 * 1. レイの方向ベクトルと軸方向ベクトルの内積（denom）を計算
 * 2. 内積の絶対値がEPSILON以下の場合、レイはキャップとほぼ平行なので交差なしと判断
 * 3. レイの原点からキャップの中心までのベクトルと軸方向の内積を計算
 * 4. この内積をdenomで割ることで、レイがキャップの平面に到達する距離を計算
 * 
 * この計算は、平面とレイの交差を計算する標準的な方法です。
 */
static inline double	cy_cap_t(t_ray ray, t_vec3 center, t_vec3 axis)
{
	double	denom;

	denom = vec3_dot(ray.dir, axis);
	if (fabs(denom) <= EPSILON)
		return (-1.0);
	return (vec3_dot(vec3_sub(center, ray.orig), axis) / denom);
}

/**
 * @brief 円柱のキャップ（底面）とレイの交差をチェックする関数
 * 
 * @param hit 交差情報を格納する構造体へのポインタ
 * @param obj 円柱オブジェクトへのポインタ
 * @param ray 交差判定に使用するレイ
 * @param cap_dir キャップの方向ベクトル（正規化されていなくてもよい）
 * 
 * この関数は、円柱のキャップ（底面）とレイの交差をチェックし、有効な交差があれば
 * 交差情報を記録します。具体的には、以下の処理を行います：
 * 1. キャップの方向（上面か下面か）を判断し、sign変数に設定（正なら上面、負なら下面）
 * 2. キャップの方向ベクトルを正規化
 * 3. キャップの中心位置を計算（円柱の中心から軸方向に半高だけ移動）
 * 4. cy_cap_t関数を使って、キャップとレイの交差距離（t）を計算
 * 5. 交差距離が無効（t ≤ EPSILON）か、すでに見つかっている交差点より遠い場合は終了
 * 6. 交差点の位置（pos）を計算
 * 7. 交差点がキャップの半径内にあるかチェック（cy_cap_valid関数を使用）
 * 8. 半径外の場合は終了
 * 9. 有効な交差が見つかった場合、交差情報を記録
 * 10. キャップの法線ベクトル（軸方向に指す）を設定
 * 11. 法線の向きを正しく調整（レイの方向と反対になるよう）
 * 
 * この関数は、cy_check_caps関数から呼び出され、円柱の上面または下面のキャップとの交差を処理します。
 */
void	cy_try_cap(t_hit_record *hit, t_obj *obj, t_ray ray, t_vec3 cap_dir)
{
	t_vec3	center;
	t_vec3	pos;
	t_vec3	axis;
	double	t;
	double	sign;

	if (vec3_len(cap_dir) > 0)
		sign = 1.0;
	else
		sign = -1.0;
	axis = vec3_normalize(cap_dir);
	center = vec3_add(obj->u_type.cy.center, vec3_scale(axis, sign
				* obj->u_type.cy.height * 0.5));
	t = cy_cap_t(ray, center, axis);
	if (t <= EPSILON || (hit->t > 0 && t >= hit->t))
		return ;
	pos = vec3_add(ray.orig, vec3_scale(ray.dir, t));
	if (!cy_cap_valid(pos, center, obj->u_type.cy.radius))
		return ;
	cy_set_record(hit, obj, pos, t);
	hit->normal = vec3_scale(axis, sign);
	cy_apply_face_orientation(hit, ray);
}
