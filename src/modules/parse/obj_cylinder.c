/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:26:10 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 22:38:51 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

void	parse_cylinder(char *line, int lnum, t_scene *scene, t_app *app)
{
	t_obj	*obj;
	double	diameter;

	obj = (t_obj *)xcalloc(1, sizeof(t_obj), app);
	obj->type = OBJ_CYLINDER;
	obj->hit = cylinder_hit;
	obj->spec = (t_color){255, 255, 255};
	obj->shininess = 32.0;
	if (!parse_vec3(&line, &obj->u_type.cy.center))
		exit_errmsg("cylinder: invalid center position", lnum, app);
	if (!parse_normal_vec3(&line, &obj->u_type.cy.axis))
		exit_errmsg("cylinder: invalid axis vector", lnum, app);
	if (!parse_f64(&line, &diameter, 0.0, INFINITY))
		exit_errmsg("cylinder: invalid diameter", lnum, app);
	obj->u_type.cy.radius = diameter / 2.0;
	if (!parse_f64(&line, &obj->u_type.cy.height, 0.0, INFINITY))
		exit_errmsg("cylinder: invalid height", lnum, app);
	if (!parse_rgb(&line, &obj->u_type.cy.color))
		exit_errmsg("cylinder: invalid color", lnum, app);
	obj->reflect = 0.0;
	try_parse_reflect(&line, &obj->reflect);
	if (!expect_line_end(&line))
		exit_errmsg("cylinder: unexpected extra parameters", lnum, app);
	add_obj(&scene->objs, obj);
}
