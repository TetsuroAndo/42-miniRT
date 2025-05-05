#include "test.h"

/* テスト用の共通変数 */
static FILE *log_file;

/* テスト環境のセットアップ */
void setup_test(void)
{
    log_file = fopen("parser_test.log", "a");
    if (!log_file)
        perror("Error opening log file for append");
}

/* テスト環境のクリーンアップ */
void cleanup_test(void)
{
    if (log_file)
    {
        fclose(log_file);
        log_file = NULL;
    }
}

/* アサーション関数 */
void assert_true(int condition, const char *message)
{
    if (!condition)
    {
        if (log_file)
            fprintf(log_file, "FAIL: %s\n", message);
        fprintf(stdout, "FAIL: %s\n", message);
    }
}

void assert_false(int condition, const char *message)
{
    assert_true(!condition, message);
}

void assert_equal_int(int expected, int actual, const char *message)
{
    if (expected != actual)
    {
        if (log_file)
            fprintf(log_file, "FAIL: %s (expected: %d, got: %d)\n", message, expected, actual);
        fprintf(stdout, "FAIL: %s (expected: %d, got: %d)\n", message, expected, actual);
    }
}

void assert_equal_double(double expected, double actual, double epsilon, const char *message)
{
    if (fabs(expected - actual) > epsilon)
    {
        if (log_file)
            fprintf(log_file, "FAIL: %s (expected: %f, got: %f)\n", message, expected, actual);
        fprintf(stdout, "FAIL: %s (expected: %f, got: %f)\n", message, expected, actual);
    }
}

void assert_equal_vec3(t_vec3 expected, t_vec3 actual, double epsilon, const char *message)
{
    if (fabs(expected.x - actual.x) > epsilon ||
        fabs(expected.y - actual.y) > epsilon ||
        fabs(expected.z - actual.z) > epsilon)
    {
        if (log_file)
        {
            fprintf(log_file, "FAIL: %s\n", message);
            fprintf(log_file, "  Expected: (%f, %f, %f)\n", expected.x, expected.y, expected.z);
            fprintf(log_file, "  Actual:   (%f, %f, %f)\n", actual.x, actual.y, actual.z);
        }
        fprintf(stdout, "FAIL: %s\n", message);
        fprintf(stdout, "  Expected: (%f, %f, %f)\n", expected.x, expected.y, expected.z);
        fprintf(stdout, "  Actual:   (%f, %f, %f)\n", actual.x, actual.y, actual.z);
    }
}

void assert_equal_color(t_color expected, t_color actual, const char *message)
{
    if (expected.r != actual.r || expected.g != actual.g || expected.b != actual.b)
    {
        if (log_file)
        {
            fprintf(log_file, "FAIL: %s\n", message);
            fprintf(log_file, "  Expected: RGB(%d, %d, %d)\n", expected.r, expected.g, expected.b);
            fprintf(log_file, "  Actual:   RGB(%d, %d, %d)\n", actual.r, actual.g, actual.b);
        }
        fprintf(stdout, "FAIL: %s\n", message);
        fprintf(stdout, "  Expected: RGB(%d, %d, %d)\n", expected.r, expected.g, expected.b);
        fprintf(stdout, "  Actual:   RGB(%d, %d, %d)\n", actual.r, actual.g, actual.b);
    }
}

/* テスト結果のログ */
void log_test_result(const char *test_name, int success)
{
    if (log_file)
    {
        fprintf(log_file, "[%s] %s\n", success ? "PASS" : "FAIL", test_name);
    }
    fprintf(stdout, "[%s] %s\n", success ? "PASS" : "FAIL", test_name);
}
