/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:33:34 by teando            #+#    #+#             */
/*   Updated: 2025/05/21 11:38:49 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_accel.h"

#define BUCKETS 12

/* 各オブジェクトの centroid を得る */
static inline t_vec3 centroid(t_aabb b)
{
    return (t_vec3){
        (b.min.x + b.max.x) * 0.5,
        (b.min.y + b.max.y) * 0.5,
        (b.min.z + b.max.z) * 0.5};
}

/* AABB 表面積 */
static inline double area(t_aabb b)
{
    t_vec3 d = vec3_sub(b.max, b.min);
    return 2.0*(d.x*d.y + d.y*d.z + d.z*d.x);
}

/* オブジェクト配列を SAH で再帰分割 */
static t_bvh *bvh_build_sah(t_obj **list, int n, t_app *app)
{
    t_bvh *node = xcalloc(1, sizeof(*node), app);

    /* バウンディングボックス生成 */
    node->box = obj_bbox(list[0]);
    for (int i=1;i<n;++i)
        node->box = aabb_merge(node->box, obj_bbox(list[i]));

    /* 葉条件: 4 個以下ならそのまま格納 */
    if (n <= 4)
    {
        node->objs = list;
        node->obj_cnt = n;
        return node;
    }

    /* 1. 最長軸を求める */
    t_vec3 diag = vec3_sub(node->box.max, node->box.min);
    int axis = (diag.x > diag.y && diag.x > diag.z) ? 0 :
               (diag.y > diag.z)                    ? 1 : 2;

    /* 2. BUCKETS 個にヒストグラム分配 */
    t_aabb bucket_bb[BUCKETS] = {0};
    int    bucket_cnt[BUCKETS] = {0};
    for (int i=0;i<n;++i)
    {
        t_vec3 cent = centroid(obj_bbox(list[i]));
        double c = ((double*)&cent)[axis];
        double start = ((double*)&node->box.min)[axis];
        double end   = ((double*)&node->box.max)[axis];
        int b = (int)(BUCKETS * (c - start) / (end - start + 1e-9));
        if (b == BUCKETS) b = BUCKETS-1;
        if (bucket_cnt[b] == 0)
            bucket_bb[b] = obj_bbox(list[i]);
        else
            bucket_bb[b] = aabb_merge(bucket_bb[b], obj_bbox(list[i]));
        ++bucket_cnt[b];
    }

    /* 3. prefix/suffix で累積表面積と個数を計算し、最小コスト分割を探す */
    double prefix_area[BUCKETS-1], suffix_area[BUCKETS-1];
    int    prefix_cnt[BUCKETS-1], suffix_cnt[BUCKETS-1];

    t_aabb running = bucket_bb[0]; int cnt = bucket_cnt[0];
    for (int i=0;i<BUCKETS-1;++i)
    {
        if (i>0){
            running = aabb_merge(running, bucket_bb[i]);
            cnt    += bucket_cnt[i];
        }
        prefix_area[i] = area(running);
        prefix_cnt[i]  = cnt;
    }
    running = bucket_bb[BUCKETS-1]; cnt = bucket_cnt[BUCKETS-1];
    for (int i=BUCKETS-2;i>=0;--i)
    {
        running = aabb_merge(running, bucket_bb[i]);
        cnt    += bucket_cnt[i];
        suffix_area[i] = area(running);
        suffix_cnt[i]  = cnt;
    }

    int best = 0; double best_cost = 1e30;
    for (int i=0;i<BUCKETS-1;++i)
    {
        double cost = prefix_cnt[i]*prefix_area[i] + suffix_cnt[i]*suffix_area[i];
        if (cost < best_cost){ best_cost = cost; best = i; }
    }

    /* 4. 配列を in-place パーティション */
    int l = 0, r = n-1;
    while (l <= r)
    {
        t_vec3 cent = centroid(obj_bbox(list[l]));
        double c = ((double*)&cent)[axis];
        double start = ((double*)&node->box.min)[axis];
        double end   = ((double*)&node->box.max)[axis];
        int b = (int)(BUCKETS * (c - start) / (end - start + 1e-9));
        if (b == BUCKETS) b = BUCKETS-1;
        if (b <= best) ++l;
        else           { t_obj *tmp=list[l]; list[l]=list[r]; list[r]=tmp; --r; }
    }
    int mid = l ? l : n/2;                       /* 保険: 空バケツ対策 */

    /* 5. 再帰 */
    node->left  = bvh_build_sah(list,        mid, app);
    node->right = bvh_build_sah(list + mid, n-mid, app);
    return node;
}

/* === public API ========================================================= */

int make_bvh(t_scene *scene, t_app *app)
{
    int n=0; 
    t_obj *o;
    
    /* まずオブジェクト数をカウント */
    for (o=scene->objs; o; o=o->next) ++n;
    
    /* 配列に格納 */
    t_obj **arr = xmalloc(sizeof(t_obj*)*n, app);
    int i = 0;
    for (o=scene->objs; o; o=o->next)
        arr[i++] = o;
        
    /* SAH版BVH構築 */
    app->bvh = bvh_build_sah(arr, n, app);
    return 0;
}
