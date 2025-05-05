#include "test.h"

void test_parse_sphere(void)
{
    t_app app;
    t_scene scene;
    char line1[] = " 0.0,0.0,20.6 12.6 255,0,0";
    char line2[] = " 10,20,30 5.5 100,150,200";
    
    setup_test();
    fprintf(stdout, "\n----- Testing parse_sphere -----\n");
    
    // 初期化
    ft_bzero(&app, sizeof(t_app));
    ft_bzero(&scene, sizeof(t_scene));
    
    // テストケース1: 標準的な球体
    parse_sphere(line1, &scene, &app);
    assert_true(scene.objs != NULL, "Scene should have an object after parsing sphere");
    if (scene.objs)
    {
        t_obj *obj = scene.objs;
        assert_equal_int(OBJ_SPHERE, obj->type, "Object type should be OBJ_SPHERE");
        assert_equal_double(0.0, obj->u.sp.center.x, 0.001, "Sphere position X should be 0.0");
        assert_equal_double(0.0, obj->u.sp.center.y, 0.001, "Sphere position Y should be 0.0");
        assert_equal_double(20.6, obj->u.sp.center.z, 0.001, "Sphere position Z should be 20.6");
        assert_equal_double(12.6, obj->u.sp.radius, 0.001, "Sphere radius should be 12.6");
        assert_equal_int(255, obj->u.sp.color.r, "Sphere color R should be 255");
        assert_equal_int(0, obj->u.sp.color.g, "Sphere color G should be 0");
        assert_equal_int(0, obj->u.sp.color.b, "Sphere color B should be 0");
    }
    
    // テストケース2: 別の値の球体
    ft_bzero(&scene, sizeof(t_scene));
    parse_sphere(line2, &scene, &app);
    assert_true(scene.objs != NULL, "Scene should have an object after parsing sphere");
    if (scene.objs)
    {
        t_obj *obj = scene.objs;
        assert_equal_int(OBJ_SPHERE, obj->type, "Object type should be OBJ_SPHERE");
        assert_equal_double(10.0, obj->u.sp.center.x, 0.001, "Sphere position X should be 10.0");
        assert_equal_double(20.0, obj->u.sp.center.y, 0.001, "Sphere position Y should be 20.0");
        assert_equal_double(30.0, obj->u.sp.center.z, 0.001, "Sphere position Z should be 30.0");
        assert_equal_double(5.5, obj->u.sp.radius, 0.001, "Sphere radius should be 5.5");
        assert_equal_int(100, obj->u.sp.color.r, "Sphere color R should be 100");
        assert_equal_int(150, obj->u.sp.color.g, "Sphere color G should be 150");
        assert_equal_int(200, obj->u.sp.color.b, "Sphere color B should be 200");
    }
    
    // 不正な入力のテストはexit_errmsgを使用しているため、ここではテストしない
    
    log_test_result("parse_sphere", 1);
    cleanup_test();
}
