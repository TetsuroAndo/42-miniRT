#include "test.h"

void test_parse_scene(void)
{
    t_app *app;
    t_scene *scene;
    char test_file[] = "/tmp/miniRT_test_scene.rt";
    int fd;
    
    setup_test();
    fprintf(stdout, "\n----- Testing parse_scene -----\n");
    
    // テスト用の一時ファイルを作成
    fd = open(test_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Failed to create test file");
        cleanup_test();
        return;
    }
    
    // 有効なシーンファイルの内容を書き込む
    dprintf(fd, "A 0.2 255,255,255\n");
    dprintf(fd, "C -50.0,0,20 0,0,1 70\n");
    dprintf(fd, "L -40.0,50.0,0.0 0.6 255,255,255\n");
    dprintf(fd, "sp 0.0,0.0,20.6 12.6 255,0,0\n");
    close(fd);
    
    // アプリケーション構造体の初期化（ヒープに確保）
    app = malloc(sizeof(t_app));
    if (!app)
    {
        perror("Failed to allocate memory for app");
        cleanup_test();
        return;
    }
    ft_bzero(app, sizeof(t_app));
    
    // parse_sceneを実行
    fprintf(stdout, "Calling parse_scene with file: %s\n", test_file);
    scene = parse_scene(test_file, app);
    if (!scene)
    {
        fprintf(stderr, "Failed to parse scene\n");
        free(app);
        cleanup_test();
        return;
    }
    fprintf(stdout, "parse_scene returned successfully\n");
    
    // シーンの内容を検証
    assert_true(scene->amb.ratio > 0, "Ambient light ratio should be set");
    assert_true(scene->cam.fov > 0, "Camera FOV should be set");
    assert_true(scene->light.bright > 0, "Light brightness should be set");
    assert_true(scene->objs != NULL, "Scene should have objects");
    
    // 不完全なシーンのテスト（これはエラーになるため、コメントアウト）
    // エラーハンドリングはexit_errmsgを使用しているため、ここではテストしない
    
    // テスト用ファイルを削除
    unlink(test_file);
    
    // メモリの解放
    if (app)
    {
        if (app->fd > 0)
            close(app->fd);
        free(app);
    }
    if (scene)
    {
        // オブジェクトリストの解放
        t_obj *obj = scene->objs;
        while (obj)
        {
            t_obj *next = obj->next;
            free(obj);
            obj = next;
        }
        free(scene);
    }
    
    log_test_result("parse_scene", 1);
    cleanup_test();
}
