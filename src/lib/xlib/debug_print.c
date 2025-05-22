/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:30:27 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/18 19:33:35 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xlib.h"
#include <stdio.h>

static void print_vec3(const char *prefix, t_vec3 v)
{
    printf("%s: (%f, %f, %f)\n", prefix, v.x, v.y, v.z);
}

static void print_color(const char *prefix, t_color c)
{
    printf("%s: RGB(%d, %d, %d)\n", prefix, c.r, c.g, c.b);
}

static void print_ambient(t_ambient amb)
{
    printf("--- Ambient Light ---\n");
    printf("Ratio: %f\n", amb.ratio);
    print_color("Color", amb.color);
}

static void print_camera(t_camera cam)
{
    printf("--- Camera ---\n");
    print_vec3("Position", cam.pos);
    print_vec3("Direction", cam.dir);
    printf("FOV: %f degrees\n", cam.fov);
}

static void print_lights(t_lights *lights)
{
    int i = 0;
    while (lights)
    {
        printf("--- Light %d ---\n", i++);
        print_vec3("Position", lights->pos);
        printf("Brightness: %f\n", lights->bright);
        print_color("Color", lights->color);
        lights = lights->next;
    }
}

static void print_object(t_obj *obj)
{
    printf("Object type: ");
    switch (obj->type)
    {
        case OBJ_SPHERE:
            printf("Sphere\n");
            print_vec3("Center", obj->u.sp.center);
            printf("Radius: %f\n", obj->u.sp.radius);
            print_color("Color", obj->u.sp.color);
            break;
        case OBJ_PLANE:
            printf("Plane\n");
            print_vec3("Point", obj->u.pl.point);
            print_vec3("Normal", obj->u.pl.normal);
            print_color("Color", obj->u.pl.color);
            break;
        case OBJ_CYLINDER:
            printf("Cylinder\n");
            print_vec3("Center", obj->u.cy.center);
            print_vec3("Axis", obj->u.cy.axis);
            printf("Radius: %f\n", obj->u.cy.radius);
            printf("Height: %f\n", obj->u.cy.height);
            print_color("Color", obj->u.cy.color);
            break;
        case OBJ_CONE:
            printf("Cone\n");
            print_vec3("Vertex", obj->u.co.vertex);
            print_vec3("Axis", obj->u.co.axis);
            printf("Angle: %f rad\n", obj->u.co.angle);
            printf("Height: %f\n", obj->u.co.height);
            print_color("Color", obj->u.co.color);
            break;
        case OBJ_HYPERBOLOID:
            printf("Hyperboloid\n");
            print_vec3("Center", obj->u.hb.center);
            print_vec3("Axis", obj->u.hb.axis);
            printf("a: %f\n", obj->u.hb.a);
            printf("b: %f\n", obj->u.hb.b);
            printf("c: %f\n", obj->u.hb.c);
            print_color("Color", obj->u.hb.color);
            break;
        case OBJ_PARABOLOID:
            printf("Paraboloid\n");
            print_vec3("Vertex", obj->u.pb.vertex);
            print_vec3("Axis", obj->u.pb.axis);
            printf("k: %f\n", obj->u.pb.k);
            printf("Height: %f\n", obj->u.pb.height);
            print_color("Color", obj->u.pb.color);
            break;
        default:
            printf("Unknown object type\n");
            break;
    }
}

static void print_objects(t_obj *objs)
{
    int i = 0;
    while (objs)
    {
        printf("\n--- Object %d ---\n", i++);
        print_object(objs);
        objs = objs->next;
    }
}

void    debug_print_scene(t_app *app)
{
    printf("\n=== Scene Debug Information ===\n\n");
    print_ambient(app->scene->amb);
    printf("\n");
    print_camera(app->scene->cam);
    printf("\n");
    print_lights(app->scene->lights);
    printf("\n");
    print_objects(app->scene->objs);
    printf("\n==============================\n");
}
