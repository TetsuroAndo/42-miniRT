/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:51:37 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/20 08:42:04 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_hit.h"

static inline double	cy_get_valid_t(double a, double b, double disc)
{
    double  sqrt_d;
    double  t1;
    double  t2;

    sqrt_d = sqrt(disc);
    t1 = (-b - sqrt_d) / (2.0 * a);
    if (t1 > EPSILON)
        return (t1);
    t2 = (-b + sqrt_d) / (2.0 * a);
    if (t2 > EPSILON)
        return (t2);
    return (-1.0);
}

static inline double	cy_solve_quadratic(double a, double b, double c)
{
    double  disc;

    disc = b * b - 4.0 * a * c;
    if (disc < 0.0)
        return (-1.0);
    return (cy_get_valid_t(a, b, disc));
}

static inline t_vec3	cy_side_normal(t_vec3 hit, t_vec3 ctr, t_vec3 axis)
{
    t_vec3  ch;
    t_vec3  radial;
    double  proj;

    ch = vec3_sub(hit, ctr);
    proj = vec3_dot(ch, axis);
    radial = vec3_sub(ch, vec3_scale(axis, proj));
    return (vec3_normalize(radial));
}

static inline void	cy_apply_face_orientation(t_hit_record *rec, t_ray ray)
{
    if (vec3_dot(rec->normal, ray.dir) > 0)
        rec->normal = vec3_scale(rec->normal, -1.0);
}

static inline void	cy_set_record(t_hit_record *rec, t_obj *obj, t_vec3 pos,
                        double t)
{
    rec->t = t;
    rec->pos = pos;
    rec->color = obj->u.cy.color;
    rec->obj = obj;
}

static inline double	cy_side_t(t_ray ray, t_vec3 oc, t_vec3 axis, double r)
{
    t_vec3  d_perp;
    t_vec3  oc_perp;
    double  a;
    double  b;
    double  c;

    d_perp = vec3_sub(ray.dir, vec3_scale(axis, vec3_dot(ray.dir, axis)));
    a = vec3_dot(d_perp, d_perp);
    if (fabs(a) < EPSILON)
        return (-1.0);
    oc_perp = vec3_sub(oc, vec3_scale(axis, vec3_dot(oc, axis)));
    b = 2.0 * vec3_dot(d_perp, oc_perp);
    c = vec3_dot(oc_perp, oc_perp) - r * r;
    return (cy_solve_quadratic(a, b, c));
}

static inline void	cy_check_side(t_hit_record *hit, t_obj *obj, t_ray ray,
                            t_vec3 axis)
{
    t_vec3  oc;
    double  t;
    double  m;
    t_vec3  pos;

    oc = vec3_sub(ray.orig, obj->u.cy.center);
    t = cy_side_t(ray, oc, axis, obj->u.cy.radius);
    if (t <= EPSILON || (hit->t > 0 && t >= hit->t))
        return ;
    pos = vec3_add(ray.orig, vec3_scale(ray.dir, t));
    m = vec3_dot(vec3_sub(pos, obj->u.cy.center), axis);
    if (fabs(m) > obj->u.cy.height * 0.5 + EPSILON)
        return ;
    cy_set_record(hit, obj, pos, t);
    hit->normal = cy_side_normal(pos, obj->u.cy.center, axis);
    cy_apply_face_orientation(hit, ray);
}

static inline int	cy_cap_valid(t_vec3 hit, t_vec3 center, double r)
{
    return (vec3_len(vec3_sub(hit, center)) <= r + EPSILON * 10);
}

static inline double	cy_cap_t(t_ray ray, t_vec3 center, t_vec3 axis)
{
    double  denom;

    denom = vec3_dot(ray.dir, axis);
    if (fabs(denom) <= EPSILON)
        return (-1.0);
    return (vec3_dot(vec3_sub(center, ray.orig), axis) / denom);
}

static inline void	cy_try_cap(t_hit_record *hit, t_obj *obj, t_ray ray,
                        t_vec3 axis, double sign)
{
    double  half_h;
    t_vec3  center;
    double  t;
    t_vec3  pos;

    half_h = obj->u.cy.height * 0.5;
    center = vec3_add(obj->u.cy.center, vec3_scale(axis, sign * half_h));
    t = cy_cap_t(ray, center, axis);
    if (t <= EPSILON || (hit->t > 0 && t >= hit->t))
        return ;
    pos = vec3_add(ray.orig, vec3_scale(ray.dir, t));
    if (!cy_cap_valid(pos, center, obj->u.cy.radius))
        return ;
    cy_set_record(hit, obj, pos, t);
    hit->normal = (sign > 0) ? axis : vec3_scale(axis, -1.0);
    cy_apply_face_orientation(hit, ray);
}

static inline void	cy_check_caps(t_hit_record *hit, t_obj *obj, t_ray ray,
                            t_vec3 axis)
{
    cy_try_cap(hit, obj, ray, axis, 1.0);
    cy_try_cap(hit, obj, ray, axis, -1.0);
}

t_hit_record	cylinder_hit(t_obj *obj, t_ray ray, t_app *app)
{
    t_hit_record    hit;
    t_vec3          axis;

    (void)app;
    hit.t = -1.0;
    axis = vec3_normalize(obj->u.cy.axis);
    cy_check_side(&hit, obj, ray, axis);
    cy_check_caps(&hit, obj, ray, axis);
    return (hit);
}
