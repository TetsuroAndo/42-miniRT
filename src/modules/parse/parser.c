/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:22:19 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/24 00:36:51 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mod_parse.h"
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>

static char	*trim_line(char *line, t_app *app)
{
	char	*trimmed;

	trimmed = xstrtrim(line, " \t\f\r\v", app);
	if (!trimmed || !*trimmed || *trimmed == '#')
		return (NULL);
	return (trimmed);
}

static void	dispatch_line(char *line, int lnum, t_scene *scene, t_app *app)
{
	static const t_dispatch	dispatch[] = {{"A", 1, parse_ambient}, {"C", 1,
		parse_camera}, {"L", 1, parse_light}, {"sp", 2, parse_sphere},
	{"pl", 2, parse_plane}, {"cy", 2, parse_cylinder}, {"", 0, NULL}};
	size_t					i;

	if (lnum >= INT_MAX)
		lnum = 0;
	i = 0;
	while (dispatch[i].len)
	{
		if (ft_strncmp(line, dispatch[i].tag, dispatch[i].len) == 0
			&& ft_isspace(line[dispatch[i].len]))
			return (dispatch[i].fn(line + dispatch[i].len, lnum, scene, app));
		++i;
	}
	if (*line != '\0' && *line != '\n')
		exit_errmsg("unknown identifier", lnum, app);
}

static void	validate_scene(t_scene *scene, t_app *app)
{
	if (!scene->amb.flag)
		exit_errmsg("missing ambient light", 0, app);
	if (!scene->cam.flag)
		exit_errmsg("missing camera", 0, app);
	if (!scene->lights)
		exit_errmsg("missing light", 0, app);
	if (!scene->objs)
		exit_errmsg("no renderable object!", 0, app);
}

t_scene	*parse_scene(char *filename, t_app *app)
{
	char			*line;
	char			*trimmed;
	t_scene			*scene;
	unsigned int	lnum;

	scene = (t_scene *)xcalloc(1, sizeof(t_scene), app);
	app->fd = xopen(filename, O_RDONLY, app);
	lnum = 0;
	while (1)
	{
		line = xget_next_line(app->fd, app);
		if (!line)
			break ;
		if (lnum < INT_MAX)
			++lnum;
		trimmed = trim_line(line, app);
		if (trimmed)
			dispatch_line(trimmed, lnum, scene, app);
	}
	xclose(&app->fd);
	validate_scene(scene, app);
	return (scene);
}

int	run_parser(int ac, char **av, t_app *app)
{
	char	*extension;

	if (ac != 2)
		return (ft_dprintf(2, "usage: %s <scene_file.rt>\n", av[0]), 1);
	extension = ft_strrchr(av[1], '.');
	if (!extension || ft_strcmp(extension, ".rt") != 0)
		return (ft_dprintf(2, "Import only <.rt> file\n"), 1);
	app->scene = parse_scene(av[1], app);
	if (!app->scene)
		return (ft_dprintf(2, "Failed to parse scene\n"), 1);
	return (0);
}
