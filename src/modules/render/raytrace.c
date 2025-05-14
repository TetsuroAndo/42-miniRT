/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:49:07 by teando            #+#    #+#             */
/*   Updated: 2025/05/14 14:04:22 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_render.h"
#include <math.h>

/* ────────────────────────────────────────────────────────────────────────── */
/*  Sphere intersection – other primitives follow the same pattern.          */
/* ────────────────────────────────────────────────────────────────────────── */
static int sphere_hit(t_sphere *sp, t_ray *ray,
                     double t_min, double t_max, t_hit_record *rec)
{
    t_vec3 oc = vec3_sub(ray->orig, sp->center);
    double a = vec3_dot(ray->dir, ray->dir);
    double half_b = vec3_dot(oc, ray->dir);
    double c = vec3_dot(oc, oc) - sp->radius * sp->radius;
    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return (0);
    double sqrt_d = sqrt(discriminant);
    double root = (-half_b - sqrt_d) / a;
    if (root < t_min || root > t_max)
    {
        root = (-half_b + sqrt_d) / a;
        if (root < t_min || root > t_max)
            return (0);
    }
    rec->t = root;
    rec->pos = vec3_new(
        ray->orig.x + root * ray->dir.x,
        ray->orig.y + root * ray->dir.y,
        ray->orig.z + root * ray->dir.z);
    rec->normal = vec3_normalize(vec3_sub(rec->pos, sp->center));
    rec->color = sp->color;
    rec->obj = (t_obj *)sp;
    return (1);
}

/* Dispatch across the linked list.  Extend with planes / cylinders etc. */
static int hit_scene(t_obj *objs, t_ray *ray,
                    double t_min, double t_max,
                    t_hit_record *closest)
{
    t_hit_record tmp;
    int          hit = 0;
    double       closest_t = t_max;

    while (objs)
    {
        if (objs->type == OBJ_SPHERE &&
            sphere_hit(&objs->u.sp, ray, t_min, closest_t, &tmp))
        {
            hit = 1;
            closest_t = tmp.t;
            *closest = tmp;
        }
        /* TODO: plane, cylinder, … */
        objs = objs->next;
    }
    return hit;
}

/* Clamp helper */
static inline unsigned char clamp_uc(double v)
{
    if (v < 0.0)
		return (0);
    if (v > 255.0)
		return (255);
    return ((unsigned char)v);
}

/* Very bare‑bones Phong‑less shading: Ambient + diffuse (Lambert). */
static t_color shade(t_app *app, t_hit_record *rec)
{
    double ar = app->scene->amb.ratio;
    double r = rec->color.r * ar;
    double g = rec->color.g * ar;
    double b = rec->color.b * ar;

    for (t_lights *li = app->scene->lights; li; li = li->next)
    {
        t_vec3  l_dir = vec3_normalize(vec3_sub(li->pos, rec->pos));
        double  diff  = fmax(0.0, vec3_dot(rec->normal, l_dir)) * li->bright;
        r += rec->color.r * diff;
        g += rec->color.g * diff;
        b += rec->color.b * diff;
    }
    return ((t_color){clamp_uc(r), clamp_uc(g), clamp_uc(b)});
}

/* Public API – sample colour along a ray (object‑space RGB). */
t_color ray_color(t_app *app, t_ray *ray)
{
    t_hit_record	rec;

    if (hit_scene(app->scene->objs, ray, 1e-3, INFINITY, &rec))
        return (shade(app, &rec));
    return ((t_color){0, 0, 0}); /* sky‑box: black */
}

/* Convenience: packed 0xT_R_G_B for mlx. */
int ray_color_trgb(t_app *app, t_ray *ray)
{
    t_color c = ray_color(app, ray);
    return (create_trgb(0, c.r, c.g, c.b));
}
