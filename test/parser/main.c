#include "test.h"

int main(void)
{
	FILE *log_file;

	/* テストログファイルを開く */
	log_file = fopen("parser_test.log", "w");
	if (!log_file)
	{
		perror("Error opening log file");
		return (EXIT_FAILURE);
	}

	/* 標準出力とログファイルの両方に出力 */
	fprintf(stdout, "========== PARSER UNIT TESTS ==========\n");
	fprintf(log_file, "========== PARSER UNIT TESTS ==========\n");
	fclose(log_file);

	/* 各テスト関数を実行 */
	test_run_parser();
	test_parse_scene();
	test_parse_ambient();
	test_parse_camera();
	test_parse_light();
	test_parse_sphere();
	test_parse_plane();
	test_parse_cylinder();
	test_parse_utils();

	/* テスト結果のサマリーを出力 */
	log_file = fopen("parser_test.log", "a");
	if (log_file)
	{
		fprintf(stdout, "\n========== TEST COMPLETED ==========\n");
		fprintf(log_file, "\n========== TEST COMPLETED ==========\n");
		fclose(log_file);
	}
	return (EXIT_SUCCESS);
}

void	exit_errmsg(char *msg, t_app *app)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit_app(app, EXIT_FAILURE);
}

void exit_app(t_app *app, int code)
{
	if (app->fd > 0)
		close(app->fd);
	ft_gc_destroy((void *)app->gc);
	free(app);
	exit(code);
}

int init_app(t_app *app)
{
	app = (t_app *)ft_calloc(sizeof(t_app), 1);
	if (!app)
		exit(1);
	app->gc = ft_gc_init();
	return (0);
}
