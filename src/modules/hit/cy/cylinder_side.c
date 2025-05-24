/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_side.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:46:13 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 20:43:00 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_hit.h"

void					cy_set_record(t_hit_record *rec, t_obj *obj, t_vec3 pos,
							double t);
void					cy_apply_face_orientation(t_hit_record *rec, t_ray ray);

/**
 * @brief 二次方程式の解のうち、有効な交差距離を返す関数
 * 
 * @param a 二次方程式のx^2の係数
 * @param b 二次方程式のxの係数
 * @param disc 判別式の値（b^2 - 4ac）
 * @return double 最も近い有効な交差距離、有効な交差がない場合は-1.0
 * 
 * この関数は、二次方程式の解のうち、有効な交差距離を返します。
 * 具体的には、以下の処理を行います：
 * 1. 判別式の平方根を計算
 * 2. 二次方程式の二つの解（t1とt2）を計算
 * 3. まず小さい方の解（t1）がEPSILONより大きいかチェック（有効な交差点かどうか）
 * 4. t1が有効ならそれを返す（最も近い交差点）
 * 5. t1が有効でない場合、大きい方の解（t2）が有効かチェック
 * 6. t2が有効ならそれを返す（レイが円柱の内部から外部に向かう場合など）
 * 7. どちらも有効でない場合は-1.0を返す（交差なし）
 */
static inline double	cy_get_valid_t(double a, double b, double disc)
{
	double	sqrt_d;
	double	t1;
	double	t2;

	sqrt_d = sqrt(disc);
	t1 = (-b - sqrt_d) / (2.0 * a);
	if (t1 > EPSILON)
		return (t1);
	t2 = (-b + sqrt_d) / (2.0 * a);
	if (t2 > EPSILON)
		return (t2);
	return (-1.0);
}

/**
 * @brief 二次方程式を解いて有効な交差距離を返す関数
 * 
 * @param a 二次方程式のx^2の係数
 * @param b 二次方程式のxの係数
 * @param c 二次方程式の定数項
 * @return double 最も近い有効な交差距離、有効な交差がない場合は-1.0
 * 
 * この関数は、二次方程式 ax^2 + bx + c = 0 を解いて、有効な交差距離を返します。
 * 具体的には、以下の処理を行います：
 * 1. 判別式（b^2 - 4ac）を計算
 * 2. 判別式が負の場合、実数解が存在しないので-1.0を返す（交差なし）
 * 3. 判別式が非負の場合、cy_get_valid_t関数を呼び出して有効な交差距離を計算
 * 
 * この関数は、円柱の側面とレイの交差を計算する際に使用されます。
 */
static inline double	cy_solve_quadratic(double a, double b, double c)
{
	double	disc;

	disc = b * b - 4.0 * a * c;
	if (disc < 0.0)
		return (-1.0);
	return (cy_get_valid_t(a, b, disc));
}

/**
 * @brief 円柱の側面とレイの交差距離を計算する関数
 * 
 * @param ray 交差判定に使用するレイ
 * @param oc レイの原点から円柱の中心までのベクトル
 * @param axis 円柱の軸方向ベクトル（正規化済み）
 * @param r 円柱の半径
 * @return double 最も近い有効な交差距離、有効な交差がない場合は-1.0
 * 
 * この関数は、円柱の側面（円筒部分）とレイの交差距離を計算します。
 * 円柱の軸に対して垂直な平面で考えることで、問題を単純化します。
 * 具体的には、以下の処理を行います：
 * 1. レイの方向ベクトルを軸方向と垂直な成分（d_perp）に分解
 * 2. レイの原点から円柱の中心までのベクトルも同様に垂直成分（oc_perp）に分解
 * 3. これらの垂直成分を使って、二次方程式の係数（a, b, c）を計算
 * 4. 係数aがほぼ0の場合、レイは円柱の軸と平行なので交差なしと判断
 * 5. cy_solve_quadratic関数を呼び出して、二次方程式を解いて有効な交差距離を返す
 * 
 * この計算は、円柱の軸に対して垂直な平面上での円とレイの交差を計算することに相当します。
 */
static inline double	cy_side_t(t_ray ray, t_vec3 oc, t_vec3 axis, double r)
{
	t_vec3	d_perp;
	t_vec3	oc_perp;
	double	a;
	double	b;
	double	c;

	d_perp = vec3_sub(ray.dir, vec3_scale(axis, vec3_dot(ray.dir, axis)));
	a = vec3_dot(d_perp, d_perp);
	if (fabs(a) < EPSILON)
		return (-1.0);
	oc_perp = vec3_sub(oc, vec3_scale(axis, vec3_dot(oc, axis)));
	b = 2.0 * vec3_dot(d_perp, oc_perp);
	c = vec3_dot(oc_perp, oc_perp) - r * r;
	return (cy_solve_quadratic(a, b, c));
}

/**
 * @brief 円柱の側面上の点における法線ベクトルを計算する関数
 * 
 * @param hit 交差点の位置ベクトル
 * @param ctr 円柱の中心位置ベクトル
 * @param axis 円柱の軸方向ベクトル（正規化済み）
 * @return t_vec3 交差点における法線ベクトル（正規化済み）
 * 
 * この関数は、円柱の側面上の点における法線ベクトルを計算します。
 * 円柱の側面上の点での法線は、中心からその点へのベクトルの軸方向と垂直な成分です。
 * 具体的には、以下の処理を行います：
 * 1. 円柱の中心から交差点までのベクトル（ch）を計算
 * 2. このベクトルの軸方向への投影成分（proj）を計算
 * 3. 軸方向成分を引いた差（radial）が、円柱の半径方向のベクトルになる
 * 4. この半径方向ベクトルを正規化して法線ベクトルとして返す
 * 
 * この法線ベクトルは、後のシェーディング計算や反射計算で使用されます。
 */
static inline t_vec3	cy_side_normal(t_vec3 hit, t_vec3 ctr, t_vec3 axis)
{
	t_vec3	ch;
	t_vec3	radial;
	double	proj;

	ch = vec3_sub(hit, ctr);
	proj = vec3_dot(ch, axis);
	radial = vec3_sub(ch, vec3_scale(axis, proj));
	return (vec3_normalize(radial));
}

/**
 * @brief 円柱の側面（円筒部分）とレイの交差をチェックする関数
 * 
 * @param hit 交差情報を格納する構造体へのポインタ
 * @param obj 円柱オブジェクトへのポインタ
 * @param ray 交差判定に使用するレイ
 * @param axis 円柱の軸方向ベクトル（正規化済み）
 * 
 * この関数は、円柱の側面（円筒部分）とレイの交差をチェックし、有効な交差があれば
 * 交差情報を記録します。具体的には、以下の処理を行います：
 * 1. レイの原点から円柱の中心までのベクトル（oc）を計算
 * 2. cy_side_t関数を使って、円柱の側面とレイの交差距離（t）を計算
 * 3. 交差距離が無効（t ≤ EPSILON）か、すでに見つかっている交差点より遠い場合は終了
 * 4. 交差点の位置（pos）を計算
 * 5. 交差点が円柱の高さ範囲内にあるかチェック（軸方向への投影成分mの絶対値が半高以下か）
 * 6. 範囲外の場合は終了
 * 7. 有効な交差が見つかった場合、交差情報を記録
 * 8. 円柱の側面上の点における法線ベクトルを計算
 * 9. 法線の向きを正しく調整（レイの方向と反対になるよう）
 * 
 * この関数は、cylinder_hit関数から呼び出され、円柱の側面との交差を処理します。
 */
void	cy_check_side(t_hit_record *hit, t_obj *obj, t_ray ray, t_vec3 axis)
{
	t_vec3	oc;
	double	t;
	double	m;
	t_vec3	pos;

	oc = vec3_sub(ray.orig, obj->u_type.cy.center);
	t = cy_side_t(ray, oc, axis, obj->u_type.cy.radius);
	if (t <= EPSILON || (hit->t > 0 && t >= hit->t))
		return ;
	pos = vec3_add(ray.orig, vec3_scale(ray.dir, t));
	m = vec3_dot(vec3_sub(pos, obj->u_type.cy.center), axis);
	if (fabs(m) > obj->u_type.cy.height * 0.5 + EPSILON)
		return ;
	cy_set_record(hit, obj, pos, t);
	hit->normal = cy_side_normal(pos, obj->u_type.cy.center, axis);
	cy_apply_face_orientation(hit, ray);
}
