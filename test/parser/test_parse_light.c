#include "test.h"

void test_parse_light(void)
{
    t_app app;
    t_scene scene;
    char line1[] = " -40.0,50.0,0.0 0.6 255,255,255";
    char line2[] = " 10,20,30 0.8 100,150,200";
    
    setup_test();
    fprintf(stdout, "\n----- Testing parse_light -----\n");
    
    // 初期化
    ft_bzero(&app, sizeof(t_app));
    ft_bzero(&scene, sizeof(t_scene));
    
    // テストケース1: 標準的なライト設定
    parse_light(line1, &scene, &app);
    assert_equal_double(-40.0, scene.light.pos.x, 0.001, "Light position X should be -40.0");
    assert_equal_double(50.0, scene.light.pos.y, 0.001, "Light position Y should be 50.0");
    assert_equal_double(0.0, scene.light.pos.z, 0.001, "Light position Z should be 0.0");
    assert_equal_double(0.6, scene.light.bright, 0.001, "Light brightness should be 0.6");
    assert_equal_int(255, scene.light.color.r, "Light color R should be 255");
    assert_equal_int(255, scene.light.color.g, "Light color G should be 255");
    assert_equal_int(255, scene.light.color.b, "Light color B should be 255");
    
    // テストケース2: 別の値のライト設定
    ft_bzero(&scene, sizeof(t_scene));
    parse_light(line2, &scene, &app);
    assert_equal_double(10.0, scene.light.pos.x, 0.001, "Light position X should be 10.0");
    assert_equal_double(20.0, scene.light.pos.y, 0.001, "Light position Y should be 20.0");
    assert_equal_double(30.0, scene.light.pos.z, 0.001, "Light position Z should be 30.0");
    assert_equal_double(0.8, scene.light.bright, 0.001, "Light brightness should be 0.8");
    assert_equal_int(100, scene.light.color.r, "Light color R should be 100");
    assert_equal_int(150, scene.light.color.g, "Light color G should be 150");
    assert_equal_int(200, scene.light.color.b, "Light color B should be 200");
    
    // 不正な入力のテストはexit_errmsgを使用しているため、ここではテストしない
    
    log_test_result("parse_light", 1);
    cleanup_test();
}
