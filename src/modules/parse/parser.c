/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:22:19 by tomsato           #+#    #+#             */
/*   Updated: 2025/05/05 02:17:50 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_parse.h"
#include <stdlib.h>

/* 行のトリミングと空行・コメント行のスキップ */
static char	*trim_line(char *line, t_app *app)
{
	char	*trimmed;

	trimmed = xstrtrim(line, " \t\f\r\v", app);
	if (!trimmed || !*trimmed || *trimmed == '#')
		return (NULL);
	return (trimmed);
}

static void	dispatch_line(char *line, t_scene *scene, t_app *app)
{
	static const t_dispatch	dispatch[] = {
		{"A", 1, parse_ambient},
		{"C", 1, parse_camera},
		{"L", 1, parse_light},
		{"sp", 2, parse_sphere},
		{"pl", 2, parse_plane},
		{"cy", 2, parse_cylinder},
		{"", 0, NULL}
	};
	size_t i;

	i = 0;
	while (dispatch[i].len)
	{
		if (ft_strncmp(line, dispatch[i].tag, dispatch[i].len) == 0
			&& ft_isspace(line[dispatch[i].len]))
			return (dispatch[i].fn(line + dispatch[i].len, scene, app));
		++i;
	}
	exit_errmsg("unknown identifier", app);
}

/* シーン検証 */
static void	validate_scene(t_scene *scene, t_app *app)
{
	if (!scene->amb.ratio)
		exit_errmsg("missing ambient light", app);
	if (!scene->cam.fov)
		exit_errmsg("missing camera", app);
	if (!scene->light.bright)
		exit_errmsg("missing light", app);
	if (!scene->objs)
		exit_errmsg("no renderable object!", app);
	/* 追加チェック: 正規化ベクトル誤差など */
}

/* メインパース関数 */
t_scene	parse_scene(char *filename, t_app *app)
{
	char	*line;
	char	*trimmed;
	t_scene	scene;

	ft_bzero(&scene, sizeof(t_scene));
	app->fd = xopen(filename, O_RDONLY, app);
	while (1)
	{
		line = xget_next_line(app->fd, app);
		if (!line)
			break ;
		trimmed = trim_line(line, app);
		if (trimmed)
			dispatch_line(trimmed, &scene, app);
	}
	xclose(app->fd);
	validate_scene(&scene, app);
	return (scene);
}
