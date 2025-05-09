// #ifndef TEST_H
// # define TEST_H

// # include "test_app.h"
// # include "libft.h"
// # include <stdio.h>
// # include <stdlib.h>
// # include <string.h>
// # include <fcntl.h>
// # include <unistd.h>
// # include <math.h>

// typedef struct s_dispatch
// {
// 	char	tag[3];
// 	uint8_t	len;
// 	void	(*fn)(char *, t_scene *, t_app *);
// }			t_dispatch;

// /* main */
// int			run_parser(int ac, char **av, t_app *app);
// t_scene		*parse_scene(char *filename, t_app *app);

// /* parse functions */
// void		parse_ambient(char *line, t_scene *scene, t_app *app);
// void		parse_camera(char *line, t_scene *scene, t_app *app);
// void		parse_light(char *line, t_scene *scene, t_app *app);
// void		parse_sphere(char *line, t_scene *scene, t_app *app);
// void		parse_plane(char *line, t_scene *scene, t_app *app);
// void		parse_cylinder(char *line, t_scene *scene, t_app *app);

// /* utils */
// int			parse_f64(char **s, double *out, double min, double max);
// int			parse_rgb(char **s, t_color *out);
// int			parse_vec3(char **s, t_vec3 *out);
// int			parse_normal_vec3(char **s, t_vec3 *out);
// int			expect_line_end(char **s);

// /* テスト関数のプロトタイプ */
// void    test_run_parser(void);
// void    test_parse_scene(void);
// void    test_parse_ambient(void);
// void    test_parse_camera(void);
// void    test_parse_light(void);
// void    test_parse_sphere(void);
// void    test_parse_plane(void);
// void    test_parse_cylinder(void);
// void    test_parse_utils(void);

// /* テストユーティリティ関数 */
// void    setup_test(void);
// void    cleanup_test(void);
// void    assert_true(int condition, const char *message);
// void    assert_false(int condition, const char *message);
// void    assert_equal_int(int expected, int actual, const char *message);
// void    assert_equal_double(double expected, double actual, double epsilon, const char *message);
// void    assert_equal_vec3(t_vec3 expected, t_vec3 actual, double epsilon, const char *message);
// void    assert_equal_color(t_color expected, t_color actual, const char *message);
// void    log_test_result(const char *test_name, int success);

// #endif