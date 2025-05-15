#include <stdio.h>
#include <stdlib.h>
#include <string.h>  /* strncpy 関数のため */
#include "test_app.h"

/* テスト環境用のグローバル変数 */
static int g_test_error_code = 0;
static char g_test_error_msg[1024] = {0};
static int g_test_error_occurred = 0;

/* エラー発生時に情報を記録する関数 */
void exit_app(t_app *app, int code)
{
	(void)app;
	fprintf(stderr, "[TEST] exit_app() called with code=%d (This would normally exit the program)\n", code);
	
	/* エラー情報を記録 */
	g_test_error_code = code;
	g_test_error_occurred = 1;
	
	/* テスト環境ではプログラムを終了しない */
}

void exit_errmsg(char *msg, t_app *app)
{
	(void)app;
	fprintf(stderr, "[TEST] exit_errmsg(): %s (This would normally exit the program)\n", msg);
	
	/* エラー情報を記録 */
	if (msg)
		strncpy(g_test_error_msg, msg, sizeof(g_test_error_msg) - 1);
	g_test_error_occurred = 1;
	
	/* テスト環境ではプログラムを終了しない */
}

/* テスト環境用のヘルパー関数 */
int test_error_occurred(void)
{
	return g_test_error_occurred;
}

int test_get_error_code(void)
{
	return g_test_error_code;
}

char *test_get_error_msg(void)
{
	return g_test_error_msg;
}

void test_reset_error(void)
{
	g_test_error_code = 0;
	g_test_error_msg[0] = '\0';
	g_test_error_occurred = 0;
}
