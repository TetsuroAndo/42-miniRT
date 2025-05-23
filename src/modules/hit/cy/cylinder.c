/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:51:37 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/24 01:21:43 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_hit.h"

void				cy_check_side(t_hit_record *hit, t_obj *obj, t_ray ray,
						t_vec3 axis);
void				cy_try_cap(t_hit_record *hit, t_obj *obj, t_ray ray,
						t_vec3 cap_dir);

/**
 * @brief 円柱との交差情報を記録する関数
 * 
 * @param rec 交差情報を格納する構造体へのポインタ
 * @param obj 円柱オブジェクトへのポインタ
 * @param pos 交差点の位置ベクトル
 * @param t レイの原点から交差点までの距離パラメータ
 * 
 * この関数は、円柱とレイの交差が発生したときに、交差情報を記録構造体に格納します。
 * 具体的には、交差距離パラメータ、交差点の位置、円柱の色、およびオブジェクトへの参照を設定します。
 * この情報は、後のレンダリング処理で使用されます。
 */
void	cy_set_record(t_hit_record *rec, t_obj *obj, t_vec3 pos, double t)
{
	rec->t = t;
	rec->pos = pos;
	rec->color = obj->u_type.cy.color;
	rec->obj = obj;
}

/**
 * @brief 法線ベクトルの向きを正しく調整する関数
 * 
 * @param rec 交差情報を格納する構造体へのポインタ
 * @param ray 交差判定に使用したレイ
 * 
 * この関数は、法線ベクトルが常にレイの方向と反対向き（入射方向と反対）になるように調整します。
 * レイの方向と法線の内積が正の場合（同じ方向を向いている場合）、法線を反転させます。
 * これは、レイがオブジェクトの内部から外部に向かっている場合や、法線の向きが逆になっている場合に必要です。
 * 正しい法線の向きは、シェーディング計算や反射計算に重要です。
 */
void	cy_apply_face_orientation(t_hit_record *rec, t_ray ray)
{
	if (vec3_dot(rec->normal, ray.dir) > 0)
		rec->normal = vec3_scale(rec->normal, -1.0);
}

/**
 * @brief 円柱の上下両方のキャップ（底面）との交差をチェックする関数
 * 
 * @param hit 交差情報を格納する構造体へのポインタ
 * @param obj 円柱オブジェクトへのポインタ
 * @param ray 交差判定に使用するレイ
 * @param axis 円柱の軸方向ベクトル（正規化済み）
 * 
 * この関数は、円柱の上下両方のキャップ（底面）とレイの交差をチェックします。
 * 具体的には、次の処理を行います：
 * 1. まず、軸方向と同じ向きのキャップ（上面）との交差をチェック
 * 2. 次に、軸方向と反対向きのキャップ（下面）との交差をチェック
 * 
 * これにより、円柱の上下両方のキャップとの交差を効率的にチェックします。
 * 各キャップとの交差は、cy_try_cap関数によって処理されます。
 */
static inline void	cy_check_caps(t_hit_record *hit, t_obj *obj, t_ray ray,
		t_vec3 axis)
{
	cy_try_cap(hit, obj, ray, axis);
	cy_try_cap(hit, obj, ray, vec3_scale(axis, -1.0));
}

/**
 * @brief 円柱とレイの交差を計算するメイン関数
 * 
 * @param obj 円柱オブジェクトへのポインタ
 * @param ray 交差判定に使用するレイ
 * @param app アプリケーション全体の状態を保持する構造体へのポインタ（この関数では使用しない）
 * @return t_hit_record 交差情報を格納した構造体。交差がない場合はtフィールドは-1.0に設定される
 * 
 * この関数は、円柱とレイの交差を計算するメイン関数です。
 * 円柱の軸方向を正規化し、円柱の交差をチェック
 * 
 * これらのチェックは、cy_check_side関数とcy_check_caps関数によって行われます。
 * 交差が見つかった場合、最も近い交差点の情報がhit構造体に格納されます。
 * 交差がない場合、hit.tは-1.0のまま返されます。
 */
t_hit_record	cylinder_hit(t_obj *obj, t_ray ray, t_app *app)
{
	t_hit_record	hit;
	t_vec3			axis;

	(void)app;
	hit.t = -1.0;
	axis = vec3_normalize(obj->u_type.cy.axis);
	cy_check_side(&hit, obj, ray, axis);
	cy_check_caps(&hit, obj, ray, axis);
	return (hit);
}
