/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:43:49 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/24 16:34:01 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"

/**
 * @brief 衝突点でのローカル照明計算を行う関数
 * 
 * @param hit 衝突情報を格納した構造体へのポインタ（位置、法線、オブジェクト情報など）
 * @param app アプリケーション全体の状態を保持する構造体へのポインタ（シーン情報を含む）
 * @return t_rgbd 計算された色をRGB double形式で返す（各成分は0.0～1.0の範囲）
 * 
 * この関数は、calculate_light_color関数（整数RGB形式で計算）を呼び出し、
 * その結果を浮動小数点数形式（t_rgbd）に変換して返します。
 * 「ローカル照明」とは、反射光を含まない、直接光源からの寄与のみを計算した色です。
 */
t_rgbd	shade_local(t_hit_record *hit, t_app *app)
{
	int	trgb;

	trgb = calculate_light_color(hit, app);
	return (trgb_to_rgbd(trgb));
}

/**
 * @brief レイトレーシングの中核となる再帰的なレイ追跡関数
 * 
 * @param ray 追跡するレイ（原点と方向を含む）
 * @param app アプリケーション全体の状態を保持する構造体へのポインタ
 * @param depth 現在の再帰の深さ（反射回数の制限に使用）
 * @return t_rgbd 計算された色をRGB double形式で返す
 * 
 * 1. レイとシーン内のオブジェクトとの交差判定
 * 2. 交差がない場合は背景色を返す
 * 3. 交差点でのローカル照明計算
 * 4. オブジェクトが反射性を持ち、最大深度に達していない場合は反射レイを計算
 * 5. 反射レイを再帰的に追跡し、その結果を反射率に応じて合成
 * 6. 最終的な色を返す
 */
t_rgbd	trace_ray(t_ray ray, t_app *app, int depth)
{
	t_vec3			r;
	t_ray			refl_ray;
	t_rgbd			refl_col;
	t_hit_record	h;
	t_rgbd			local;

	h = intersect_ray(ray, app, INFINITY);
	if (h.t <= 0.0 || !h.obj)
		return (rgbd_scale((t_rgbd){0.625, 0.84375, 0.93359375},
			app->scene->amb.ratio));
	local = shade_local(&h, app);
	refl_col = (t_rgbd){0, 0, 0};
	if (h.obj->reflect > 0.0 && depth < MAX_DEPTH)
	{
		r = vec3_sub(ray.dir, vec3_scale(h.normal, 2.0 * vec3_dot(ray.dir,
						h.normal)));
		refl_ray = (t_ray){.orig = vec3_add(h.pos, vec3_scale(h.normal,
					SHADOW_BIAS)), .dir = vec3_normalize(r)};
		refl_col = trace_ray(refl_ray, app, depth + 1);
	}
	return (rgbd_add(rgbd_scale(local, 1.0 - h.obj->reflect),
			rgbd_scale(refl_col, h.obj->reflect)));
}

/**
 * @brief 影（シャドウ）判定を行う関数
 * 
 * @param hit 衝突点の情報を格納した構造体へのポインタ
 * @param light 判定対象の光源情報を格納した構造体へのポインタ
 * @param app アプリケーション全体の状態を保持する構造体へのポインタ
 * @return int 影の中にある場合は1、そうでない場合は0を返す
 * 
 * 1. 衝突点から光源への方向ベクトルを計算
 * 2. 衝突点から光源までの距離を計算
 * 3. 衝突点から光源方向へのシャドウレイを生成（自己交差を避けるためにSHADOW_BIASだけオフセット）
 * 4. シャドウレイと他のオブジェクトとの交差判定
 * 5. 交差がある場合（t > 0.0）は影の中にあると判断
 */
int	is_shadow(t_hit_record *hit, t_lights *light, t_app *app)
{
	const t_vec3		dir = vec3_normalize(vec3_sub(light->pos, hit->pos));
	const double		t_max = vec3_len(dir);
	const t_ray			shadow_ray = {.orig = vec3_add(hit->pos,
			vec3_scale(hit->normal, SHADOW_BIAS)), .dir = dir};
	const t_hit_record	s = intersect_ray(shadow_ray, app, t_max);

	return (s.t > 0.0);
}

/**
 * @brief レイとシーン内のすべてのオブジェクトとの交差判定を行う関数
 * 
 * @param ray 交差判定を行うレイ（原点と方向を含む）
 * @param app アプリケーション全体の状態を保持する構造体へのポインタ
 * @param t_max 交差判定を行う最大距離（これより遠い交差点は無視される）
 * @return t_hit_record 最も近い交差点の情報を格納した構造体
 * 
 * 1. シーン内のすべてのオブジェクトに対して線形探索を行う
 * 2. 各オブジェクトの衝突判定関数（o->hit）を呼び出す
 * 3. 有効な交差点（t > 0.0）のうち、最も近いものを記録
 * 4. 交差するオブジェクトがない場合はt=0.0を設定して返す
 * 
 * 注：この実装はシンプルな線形探索による交差テストです。
 * 大規模なシーンでは空間分割などの高速化手法が必要になります。
 */
t_hit_record	intersect_ray(t_ray ray, t_app *app, double t_max)
{
	t_hit_record	rec;
	t_hit_record	closest;
	t_obj			*o;

	closest = (t_hit_record){.t = t_max, .obj = NULL};
	o = app->scene->objs;
	while (o)
	{
		rec = o->hit(o, ray, app);
		if (rec.t > 0.0 && rec.t < closest.t)
			closest = rec;
		o = o->next;
	}
	if (!closest.obj)
		closest.t = 0.0;
	return (closest);
}
