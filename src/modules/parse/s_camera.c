/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:23:31 by teando            #+#    #+#             */
/*   Updated: 2025/05/24 00:38:09 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

void	parse_camera(char *line, int lnum, t_scene *scene, t_app *app)
{
	if (scene->cam.flag)
		exit_errmsg("duplicate camera", lnum, app);
	scene->cam.flag = 1;
	if (!parse_vec3(&line, &scene->cam.pos))
		exit_errmsg("camera: invalid position (expected x,y,z)", lnum, app);
	if (!parse_normal_vec3(&line, &scene->cam.dir))
		exit_errmsg("camera: invalid direction (expected normalized x,y,z)",
			lnum, app);
	if (!parse_f64(&line, &scene->cam.fov, 0.0, 180.0))
		exit_errmsg("camera: invalid FOV (expected 0-180)", lnum, app);
	if (!expect_line_end(&line))
		exit_errmsg("camera: unexpected extra parameters", lnum, app);
}
