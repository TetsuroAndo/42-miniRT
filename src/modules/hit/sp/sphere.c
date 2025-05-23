/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:50:20 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/22 20:49:24 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_hit.h"

/**
 * @brief 球体との交差情報を記録する関数
 * 
 * @param rec 交差情報を格納する構造体へのポインタ
 * @param obj 球体オブジェクトへのポインタ
 * @param ray 交差判定に使用したレイ
 * @param t レイの原点から交差点までの距離パラメータ
 * 
 * この関数は、球体とレイの交差が発生したときに、交差情報を記録構造体に格納します。
 * 具体的には、以下の処理を行います：
 * 1. 交差距離パラメータ（t）を記録
 * 2. 交差点の位置（pos）を計算（レイの原点からレイの方向にt倍した点）
 * 3. 交差点での法線ベクトルを計算（交差点から球体の中心へのベクトルを正規化）
 * 4. レイが球体の内側から外側に向かっている場合（レイの方向と法線の内積が正）、
 *    法線を反転させて外向きにする
 * 5. 球体の色を記録
 * 6. オブジェクトへの参照を記録
 * 
 * この情報は、後のシェーディング計算や反射計算で使用されます。
 */
static inline void	fill_rec(t_hit_record *rec, t_obj *obj, t_ray ray, double t)
{
	rec->t = t;
	rec->pos = vec3_add(ray.orig, vec3_scale(ray.dir, t));
	/* 法線を求める (pos - center) / r */
	rec->normal = vec3_normalize(vec3_sub(rec->pos, obj->u_type.sp.center));
	/* レイが球の内側から出て行く場合は外向きに反転させる */
	if (vec3_dot(ray.dir, rec->normal) > 0.0)
		rec->normal = vec3_scale(rec->normal, -1.0);
	rec->color = obj->u_type.sp.color;
	rec->obj = obj;
}

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
 * 3. まず小さい方の解（t1）がEPSILONより大きいかチェック
 * 4. t1が有効ならそれを返す（レイが球体の外側から入る場合の交差点）
 * 5. t1が有効でない場合、大きい方の解（t2）が有効かチェック
 * 6. t2が有効ならそれを返す（レイが球体の内側から外側に向かう場合など）
 * 7. どちらも有効でない場合は-1.0を返す（交差なし）
 */
static inline double	get_valid_t(double a, double b, double disc)
{
	const double	sqrt_d = sqrt(disc);
	const double	t1 = (-b - sqrt_d) / (2 * a);
	const double	t2 = (-b + sqrt_d) / (2 * a);

	if (t1 > EPSILON)
		return (t1); /* 手前側ヒット */
	if (t2 > EPSILON)
		return (t2); /* 内部にいた場合など */
	return (-1.0);
}

/**
 * @brief 球体とレイの交差を計算するための二次方程式を解く関数
 * 
 * @param oc レイの原点から球体の中心までのベクトル
 * @param dir レイの方向ベクトル（正規化済みを想定）
 * @param r2 球体の半径の二乗
 * @return double 最も近い有効な交差距離、有効な交差がない場合は-1.0
 * 
 * この関数は、球体とレイの交差を計算するための二次方程式を解きます。
 * 球体とレイの交差は、以下の二次方程式で表されます：
 * |O + t*D - C|^2 = r^2
 * ここで、Oはレイの原点、Dはレイの方向、Cは球体の中心、rは球体の半径です。
 * 
 * この関数は、以下の処理を行います：
 * 1. 二次方程式の係数（a, b, c）を計算
 *    a = D・D
 *    b = 2(O-C)・D
 *    c = (O-C)・(O-C) - r^2
 * 2. 判別式（b^2 - 4ac）を計算
 * 3. 判別式が負の場合、交差はないので-1.0を返す
 * 4. 判別式が非負の場合、get_valid_t関数を呼び出して有効な交差距離を計算
 */
static inline double	solve_quadratic(const t_vec3 oc, const t_vec3 dir,
		const double r2)
{
	const double	a = vec3_dot(dir, dir);
	const double	b = 2.0 * vec3_dot(oc, dir);
	const double	c = vec3_dot(oc, oc) - r2;
	const double	disc = b * b - 4.0 * a * c;

	if (disc < 0.0)
		return (-1.0);
	return (get_valid_t(a, b, disc));
}

/**
 * @brief 球体とレイの交差を計算するメイン関数
 * 
 * @param obj 球体オブジェクトへのポインタ
 * @param ray 交差判定に使用するレイ
 * @param app アプリケーション全体の状態を保持する構造体へのポインタ（この関数では使用しない）
 * @return t_hit_record 交差情報を格納した構造体。交差がない場合はtフィールドは-1.0に設定される
 * 
 * この関数は、球体とレイの交差を計算するメイン関数です。
 * 具体的には、以下の処理を行います：
 * 1. レイの原点から球体の中心までのベクトル（oc）を計算
 * 2. 交差情報を格納する構造体（rec）を初期化（t = -1.0で交差なしを表す）
 * 3. solve_quadratic関数を使って、球体とレイの交差距離（t）を計算
 * 4. 有効な交差があれば（t > 0.0）、fill_rec関数を呼び出して交差情報を記録
 * 5. 交差情報を返す
 * 
 * この関数は、レイトレーシングの中核となる交差判定の一部で、球体との交差を処理します。
 */
t_hit_record	sphere_hit(t_obj *obj, t_ray ray, t_app *app)
{
	t_hit_record	rec;
	double			t;
	const t_vec3	oc = vec3_sub(ray.orig, obj->u_type.sp.center);

	(void)app;
	rec.t = -1.0; /* ヒットなしで初期化 */
	t = solve_quadratic(oc, ray.dir, obj->u_type.sp.radius
			* obj->u_type.sp.radius);
	if (t > 0.0)
		fill_rec(&rec, obj, ray, t);
	return (rec);
}
