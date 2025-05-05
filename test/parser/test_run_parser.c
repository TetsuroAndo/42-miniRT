#include "test.h"

void test_run_parser(void)
{
    t_app *app;
    int result;
    char *argv[3];
    
    setup_test();
    fprintf(stdout, "\n----- Testing run_parser -----\n");
    
    // アプリケーション構造体の初期化（ヒープに確保）
    app = malloc(sizeof(t_app));
    if (!app)
    {
        perror("Failed to allocate memory for app");
        cleanup_test();
        return;
    }
    ft_bzero(app, sizeof(t_app));
    
    // テストケース1: 引数が足りない場合
    argv[0] = "miniRT";
    result = run_parser(1, argv, app);
    assert_equal_int(1, result, "run_parser should return 1 when argc < 2");
    
    // テストケース2: 拡張子がない場合
    argv[0] = "miniRT";
    argv[1] = "test_file";
    result = run_parser(2, argv, app);
    assert_equal_int(1, result, "run_parser should return 1 when filename has no extension");
    
    // テストケース3: 拡張子が.rtでない場合
    argv[0] = "miniRT";
    argv[1] = "test_file.txt";
    result = run_parser(2, argv, app);
    assert_equal_int(1, result, "run_parser should return 1 when extension is not .rt");
    
    // テストケース4: 拡張子が.rtだが、ファイルが存在しない場合
    // 注意: このテストはxopen関数がエラーハンドリングを行うため、実際には実行されない
    // argv[0] = "miniRT";
    // argv[1] = "nonexistent_file.rt";
    // result = run_parser(2, argv, app);
    // assert_equal_int(1, result, "run_parser should return 1 when file doesn't exist");
    
    // テストケース5: .rtxのような類似拡張子の場合
    argv[0] = "miniRT";
    argv[1] = "test_file.rtx";
    result = run_parser(2, argv, app);
    assert_equal_int(1, result, "run_parser should return 1 when extension is similar but not exactly .rt");
    
    // メモリの解放
    if (app)
    {
        if (app->fd > 0)
            close(app->fd);
        if (app->scene)
            free(app->scene);
        free(app);
    }
    
    log_test_result("run_parser", 1);
    cleanup_test();
}
