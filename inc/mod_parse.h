/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:58:33 by teando            #+#    #+#             */
/*   Updated: 2025/05/05 10:19:42 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOD_PARSE_H
# define MOD_PARSE_H

# include "xlib.h"
# include "rt_obj.h"
# include "rt_scene.h"
# include "rt_vec.h"
# include <math.h>
# include <stdlib.h>

typedef struct s_app	t_app;
typedef struct s_scene	t_scene;

typedef struct s_dispatch
{
	char	tag[3];
	uint8_t	len;
	void	(*fn)(char *, t_scene *, t_app *);
}			t_dispatch;

/* main */
int			run_parser(int ac, char **av, t_app *app);
t_scene		*parse_scene(char *filename, t_app *app);

/* parse functions */
void		parse_ambient(char *line, t_scene *scene, t_app *app);
void		parse_camera(char *line, t_scene *scene, t_app *app);
void		parse_light(char *line, t_scene *scene, t_app *app);
void		parse_sphere(char *line, t_scene *scene, t_app *app);
void		parse_plane(char *line, t_scene *scene, t_app *app);
void		parse_cylinder(char *line, t_scene *scene, t_app *app);

/* utils */
int			parse_f64(char **s, double *out, double min, double max);
int			parse_rgb(char **s, t_color *out);
int			parse_vec3(char **s, t_vec3 *out);
int			parse_normal_vec3(char **s, t_vec3 *out);
int			expect_line_end(char **s);
void		add_obj(t_obj **head, t_obj *obj);

#endif