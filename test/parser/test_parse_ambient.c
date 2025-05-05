#include "test.h"

void test_parse_ambient(void)
{
    t_app app;
    t_scene scene;
    char line1[] = " 0.2 255,255,255";
    char line2[] = " 0.5 100,150,200";
    char line3[] = " 1.0 0,0,0";
    
    setup_test();
    fprintf(stdout, "\n----- Testing parse_ambient -----\n");
    
    // 初期化
    ft_bzero(&app, sizeof(t_app));
    ft_bzero(&scene, sizeof(t_scene));
    
    // テストケース1: 標準的なアンビエントライト
    parse_ambient(line1, &scene, &app);
    assert_equal_double(0.2, scene.amb.ratio, 0.001, "Ambient ratio should be 0.2");
    assert_equal_int(255, scene.amb.color.r, "Ambient color R should be 255");
    assert_equal_int(255, scene.amb.color.g, "Ambient color G should be 255");
    assert_equal_int(255, scene.amb.color.b, "Ambient color B should be 255");
    
    // テストケース2: 別の値のアンビエントライト
    ft_bzero(&scene, sizeof(t_scene));
    parse_ambient(line2, &scene, &app);
    assert_equal_double(0.5, scene.amb.ratio, 0.001, "Ambient ratio should be 0.5");
    assert_equal_int(100, scene.amb.color.r, "Ambient color R should be 100");
    assert_equal_int(150, scene.amb.color.g, "Ambient color G should be 150");
    assert_equal_int(200, scene.amb.color.b, "Ambient color B should be 200");
    
    // テストケース3: 最大値のアンビエントライト
    ft_bzero(&scene, sizeof(t_scene));
    parse_ambient(line3, &scene, &app);
    assert_equal_double(1.0, scene.amb.ratio, 0.001, "Ambient ratio should be 1.0");
    assert_equal_int(0, scene.amb.color.r, "Ambient color R should be 0");
    assert_equal_int(0, scene.amb.color.g, "Ambient color G should be 0");
    assert_equal_int(0, scene.amb.color.b, "Ambient color B should be 0");
    
    // 不正な入力のテストはexit_errmsgを使用しているため、ここではテストしない
    
    log_test_result("parse_ambient", 1);
    cleanup_test();
}
