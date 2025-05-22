/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_ambient.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:23:16 by teando            #+#    #+#             */
/*   Updated: 2025/05/22 22:19:30 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"

void	parse_ambient(char *line, int lnum, t_scene *scene, t_app *app)
{
	static int	seen_ambient = 0;

	if (seen_ambient)
		exit_errmsg("duplicate ambient light", lnum, app);
	seen_ambient = 1;
	if (!parse_f64(&line, &scene->amb.ratio, 0.0, 1.0))
		exit_errmsg("ambient: invalid ratio (expected 0.0-1.0)", lnum, app);
	if (!parse_rgb(&line, &scene->amb.color))
		exit_errmsg("ambient: invalid color (expected R,G,B in 0-255)", lnum,
			app);
	if (!expect_line_end(&line))
		exit_errmsg("ambient: unexpected extra parameters", lnum, app);
}
