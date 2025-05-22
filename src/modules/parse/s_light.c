/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:23:51 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 22:19:48 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

void	parse_light(char *line, int lnum, t_scene *scene, t_app *app)
{
	t_lights	*light;

	light = (t_lights *)xcalloc(1, sizeof(t_lights), app);
	if (!parse_vec3(&line, &light->pos))
		exit_errmsg("light: invalid position (expected x,y,z)", lnum, app);
	if (!parse_f64(&line, &light->bright, 0.0, 1.0))
		exit_errmsg("light: invalid brightness (expected 0.0-1.0)", lnum, app);
	if (*line && !expect_line_end(&line))
	{
		if (!parse_rgb(&line, &light->color))
			exit_errmsg("light: invalid color (expected R,G,B in 0-255)", lnum,
				app);
	}
	else
		light->color = (t_color){255, 255, 255};
	if (!expect_line_end(&line))
		exit_errmsg("light: unexpected extra parameters", lnum, app);
	light->next = scene->lights;
	scene->lights = light;
}
