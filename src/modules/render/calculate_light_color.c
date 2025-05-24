/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_light_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:08:24 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/22 21:11:02 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"

/**
 * @brief 拡散反射（ディフューズ）の色計算を行う関数
 * 
 * @param sum 計算結果を格納するベクトルへのポインタ（累積値）
 * @param hit 衝突情報を格納した構造体へのポインタ
 * @param light_col 光源の色情報へのポインタ
 * @param kd 拡散反射係数（ディフューズ係数）
 * 
 * この関数は、オブジェクトの色と光源の色を掛け合わせ、拡散反射係数を適用して
 * 拡散反射による色の寄与を計算します。計算結果はsumに累積されます。
 * 各色成分（RGB）は0.0～1.0の範囲の浮動小数点数で表現されます。
 */
static inline void	apply_diffuse(t_vec3 *sum, const t_hit_record *hit,
		const t_color *light_col, double kd)
{
	sum->x += (hit->color.r / 255.0) * (light_col->r / 255.0) * kd;
	sum->y += (hit->color.g / 255.0) * (light_col->g / 255.0) * kd;
	sum->z += (hit->color.b / 255.0) * (light_col->b / 255.0) * kd;
}

/**
 * @brief 鏡面反射（スペキュラー）の色計算を行う関数
 * 
 * @param sum 計算結果を格納するベクトルへのポインタ（累積値）
 * @param hit 衝突情報を格納した構造体へのポインタ
 * @param light_col 光源の色情報へのポインタ
 * @param ks 鏡面反射係数（スペキュラー係数）
 * 
 * この関数は、オブジェクトの鏡面反射色（spec）と光源の色を掛け合わせ、
 * 鏡面反射係数を適用して鏡面反射による色の寄与を計算します。
 * 計算結果はsumに累積されます。
 * 各色成分（RGB）は0.0～1.0の範囲の浮動小数点数で表現されます。
 */
static inline void	apply_specular(t_vec3 *sum, const t_hit_record *hit,
		const t_color *light_col, double ks)
{
	sum->x += (hit->obj->spec.r / 255.0) * (light_col->r / 255.0) * ks;
	sum->y += (hit->obj->spec.g / 255.0) * (light_col->g / 255.0) * ks;
	sum->z += (hit->obj->spec.b / 255.0) * (light_col->b / 255.0) * ks;
}

/**
 * @brief 1つの光源からの光の寄与を計算する関数
 * 
 * @param sum 計算結果を格納するベクトルへのポインタ（累積値）
 * @param hit 衝突情報を格納した構造体へのポインタ
 * @param l 光源情報を格納した構造体へのポインタ
 * @param view_dir 視線方向ベクトル（カメラから衝突点への方向の反対）
 * 
 * この関数は以下の処理を行います：
 * 1. 衝突点から光源への方向ベクトルを計算
 * 2. 衝突点から光源までの距離を計算
 * 3. 距離に基づく光の減衰（アテニュエーション）を計算
 * 4. 拡散反射係数（kd）と鏡面反射係数（ks）を計算
 * 5. 拡散反射と鏡面反射の寄与を合計に加算
 * 
 * 光の強さは距離の二乗に反比例して減衰します（逆二乗の法則）。
 */
static inline void	apply_light_contrib(t_vec3 *sum, const t_hit_record *hit,
		const t_lights *l, const t_vec3 view_dir)
{
	const t_vec3	light_dir = vec3_normalize(vec3_sub(l->pos, hit->pos));
	const double	dist = vec3_len(vec3_sub(l->pos, hit->pos));
	const double	atten = l->bright * 42 / (dist * dist + 1.0);
	double			kd;
	double			ks;

	kd = calc_kd(hit, light_dir, atten);
	ks = calc_ks(hit, light_dir, view_dir, atten);
	apply_diffuse(sum, hit, &l->color, kd);
	apply_specular(sum, hit, &l->color, ks);
}

/**
 * @brief HDRカラーをLDR範囲（0.0～1.0）に変換するトーンマッピング関数
 * 
 * @param color 変換するカラーベクトルへのポインタ（入力と出力を兼ねる）
 * 
 * この関数は、高ダイナミックレンジ（HDR）の色値を、ディスプレイで表示可能な
 * 低ダイナミックレンジ（LDR、0.0～1.0）に変換します。
 * 使用しているのはシンプルなReinhard式トーンマッピングで、最大成分に基づいて
 * スケーリングを行います。これにより、明るい部分が白く飽和せずに自然な見た目になります。
 */
static inline void	apply_tone_mapping(t_vec3 *color)
{
	const double	max_comp = fmax(color->x, fmax(color->y, color->z));
	const double	hdr_scale = 1.0 / (1.0 + max_comp);

	color->x *= hdr_scale;
	color->y *= hdr_scale;
	color->z *= hdr_scale;
}

/**
 * @brief 衝突点での最終的な色を計算する関数
 * 
 * @param hit 衝突情報を格納した構造体へのポインタ
 * @param app アプリケーション全体の状態を保持する構造体へのポインタ
 * @return int 計算された色をTRGB形式（32ビット整数）で返す
 * 
 * この関数は以下の処理を行います：
 * 1. アンビエント（環境光）の寄与を計算
 * 2. シーン内のすべての光源に対して処理を繰り返す
 * 3. 各光源について影判定を行い、影の中にない場合のみ光の寄与を計算
 * 4. 拡散反射と鏡面反射の寄与を合計
 * 5. トーンマッピングを適用してHDRからLDRへ変換
 * 6. 最終的な色をTRGB形式に変換して返す
 * 
 * この関数は、物理ベースのレンダリングを簡略化したモデルを使用しています。
 * アンビエント、ディフューズ、スペキュラーの各要素を計算し、最終的な色を決定します。
 */
int	calculate_light_color(t_hit_record *hit, t_app *app)
{
	const t_color	amb_col = app->scene->amb.color;
	const double	amb_ratio = app->scene->amb.ratio;
	t_vec3			sum;
	const t_vec3	view_dir = vec3_normalize(vec3_sub(app->scene->cam.pos,
				hit->pos));
	t_lights		*l;

	sum = vec3_new((hit->color.r / 255.0) * (amb_col.r / 255.0) * amb_ratio,
			(hit->color.g / 255.0) * (amb_col.g / 255.0) * amb_ratio,
			(hit->color.b / 255.0) * (amb_col.b / 255.0) * amb_ratio);
	l = app->scene->lights;
	while (l)
	{
		if (!is_shadow(hit, l, app))
			apply_light_contrib(&sum, hit, l, view_dir);
		l = l->next;
	}
	apply_tone_mapping(&sum);
	return (create_trgb(0, (int)(sum.x * 255.0 + 0.5), (int)(sum.y * 255.0
		+ 0.5), (int)(sum.z * 255.0 + 0.5)));
}
