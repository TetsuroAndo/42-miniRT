#include "test.h"

void test_parse_camera(void)
{
    t_app app;
    t_scene scene;
    char line1[] = " -50.0,0,20 0,0,1 70";
    char line2[] = " 0,10,-5 1,0,0 90";
    
    setup_test();
    fprintf(stdout, "\n----- Testing parse_camera -----\n");
    
    // 初期化
    ft_bzero(&app, sizeof(t_app));
    ft_bzero(&scene, sizeof(t_scene));
    
    // テストケース1: 標準的なカメラ設定
    parse_camera(line1, &scene, &app);
    assert_equal_double(-50.0, scene.cam.pos.x, 0.001, "Camera position X should be -50.0");
    assert_equal_double(0.0, scene.cam.pos.y, 0.001, "Camera position Y should be 0.0");
    assert_equal_double(20.0, scene.cam.pos.z, 0.001, "Camera position Z should be 20.0");
    assert_equal_double(0.0, scene.cam.dir.x, 0.001, "Camera direction X should be 0.0");
    assert_equal_double(0.0, scene.cam.dir.y, 0.001, "Camera direction Y should be 0.0");
    assert_equal_double(1.0, scene.cam.dir.z, 0.001, "Camera direction Z should be 1.0");
    assert_equal_double(70.0, scene.cam.fov, 0.001, "Camera FOV should be 70.0");
    
    // テストケース2: 別の値のカメラ設定
    ft_bzero(&scene, sizeof(t_scene));
    parse_camera(line2, &scene, &app);
    assert_equal_double(0.0, scene.cam.pos.x, 0.001, "Camera position X should be 0.0");
    assert_equal_double(10.0, scene.cam.pos.y, 0.001, "Camera position Y should be 10.0");
    assert_equal_double(-5.0, scene.cam.pos.z, 0.001, "Camera position Z should be -5.0");
    assert_equal_double(1.0, scene.cam.dir.x, 0.001, "Camera direction X should be 1.0");
    assert_equal_double(0.0, scene.cam.dir.y, 0.001, "Camera direction Y should be 0.0");
    assert_equal_double(0.0, scene.cam.dir.z, 0.001, "Camera direction Z should be 0.0");
    assert_equal_double(90.0, scene.cam.fov, 0.001, "Camera FOV should be 90.0");
    
    // 不正な入力のテストはexit_errmsgを使用しているため、ここではテストしない
    
    log_test_result("parse_camera", 1);
    cleanup_test();
}
