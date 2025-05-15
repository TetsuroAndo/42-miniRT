/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_obj.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:30:28 by teando            #+#    #+#             */
/*   Updated: 2025/05/15 17:58:12 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OBJ_H
# define RT_OBJ_H

# include "rt_vec.h"

/* --- 前方宣言 ------------------------------------------------------- */
struct s_app;           typedef struct s_app        t_app;
struct s_obj;           typedef struct s_obj        t_obj;
struct s_hit_record;    typedef struct s_hit_record t_hit_record;
struct s_ray;           typedef struct s_ray        t_ray;

/*======================================================================
**  個別オブジェクト構造体
**====================================================================*/

/* ● 球 ---------------------------------------------------------------- */
typedef struct s_sphere
{
    t_vec3      center;     /* 中心座標                */
    double      radius;     /* 半径                    */
    t_color     color;      /* 表面色 (0‑255 RGB)      */
}   t_sphere;

/* ● 平面 -------------------------------------------------------------- */
typedef struct s_plane
{
    t_vec3      point;      /* 平面上の 1 点            */
    t_vec3      normal;     /* 単位法線ベクトル         */
    t_color     color;      /* 表面色                   */
}   t_plane;

/* ● 円柱 -------------------------------------------------------------- */
typedef struct s_cylinder
{
    t_vec3      center;     /* 中心軸上の基準点          */
    t_vec3      axis;       /* 単位軸ベクトル            */
    double      radius;     /* 半径                      */
    double      height;     /* 高さ                      */
    t_color     color;      /* 表面色                    */
}   t_cylinder;

/* ● 円錐 -------------------------------------------------------------- */
typedef struct s_cone
{
    t_vec3      vertex;     /* 頂点位置                  */
    t_vec3      axis;       /* 単位軸ベクトル            */
    double      angle;      /* 半頂角 (rad)              */
    double      height;     /* 高さ                      */
    t_color     color;      /* 表面色                    */
}   t_cone;

/* ● 双曲面 ------------------------------------------------------------ */
typedef struct s_hyperboloid
{
    t_vec3      center;     /* 中心位置                  */
    t_vec3      axis;       /* 単位軸ベクトル            */
    double      a;          /* x 方向半径                */
    double      b;          /* y 方向半径                */
    double      c;          /* z 方向係数                */
    t_color     color;      /* 表面色                    */
}   t_hyperboloid;

/* ● 放物面 ------------------------------------------------------------ */
typedef struct s_paraboloid
{
    t_vec3      vertex;     /* 頂点位置                  */
    t_vec3      axis;       /* 単位軸ベクトル            */
    double      k;          /* 開口度 (z = k·r^2)        */
    double      height;     /* 有限放物面の切断高さ       */
    t_color     color;      /* 表面色                    */
}   t_paraboloid;

/*======================================================================
**  汎用オブジェクトラッパー
**====================================================================*/

typedef enum e_obj_type
{
    OBJ_SPHERE,
    OBJ_PLANE,
    OBJ_CYLINDER,
    OBJ_CONE,
    OBJ_HYPERBOLOID,
    OBJ_PARABOLOID
}   t_obj_type;

struct s_obj
{
    t_obj_type          type;
    union
    {
        t_sphere        sp;
        t_plane         pl;
        t_cylinder      cy;
        t_cone          co;
        t_hyperboloid   hb;
        t_paraboloid    pb;
    }               u;
    struct s_obj    *next;
    t_hit_record    (*hit)(struct s_obj *obj, t_ray ray, t_app *app);
};

#endif
