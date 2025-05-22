/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:24:58 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 22:19:06 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

void	parse_sphere(char *line, int lnum, t_scene *scene, t_app *app)
{
	t_obj	*obj;
	double	diameter;

	obj = (t_obj *)xcalloc(1, sizeof(t_obj), app);
	obj->type = OBJ_SPHERE;
	obj->hit = sphere_hit;
	obj->spec = (t_color){255, 255, 255};
	obj->shininess = 32.0;
	if (!parse_vec3(&line, &obj->u_type.sp.center))
		exit_errmsg("sphere: invalid center position", lnum, app);
	if (!parse_f64(&line, &diameter, 0.0, INFINITY))
		exit_errmsg("sphere: invalid diameter", lnum, app);
	obj->u_type.sp.radius = diameter / 2.0;
	if (!parse_rgb(&line, &obj->u_type.sp.color))
		exit_errmsg("sphere: invalid color", lnum, app);
	obj->reflect = 0.0;
	try_parse_reflect(&line, &obj->reflect);
	if (!expect_line_end(&line))
		exit_errmsg("sphere: unexpected extra parameters", lnum, app);
	add_obj(&scene->objs, obj);
}
