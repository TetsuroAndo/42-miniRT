#include "test.h"

void test_parse_plane(void)
{
    t_app app;
    t_scene scene;
    char line1[] = " 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225";
    char line2[] = " 10,20,30 1,0,0 100,150,200";
    
    setup_test();
    fprintf(stdout, "\n----- Testing parse_plane -----\n");
    
    // 初期化
    ft_bzero(&app, sizeof(t_app));
    ft_bzero(&scene, sizeof(t_scene));
    
    // テストケース1: 標準的な平面
    parse_plane(line1, &scene, &app);
    assert_true(scene.objs != NULL, "Scene should have an object after parsing plane");
    if (scene.objs)
    {
        t_obj *obj = scene.objs;
        assert_equal_int(OBJ_PLANE, obj->type, "Object type should be OBJ_PLANE");
        assert_equal_double(0.0, obj->u.pl.point.x, 0.001, "Plane position X should be 0.0");
        assert_equal_double(0.0, obj->u.pl.point.y, 0.001, "Plane position Y should be 0.0");
        assert_equal_double(-10.0, obj->u.pl.point.z, 0.001, "Plane position Z should be -10.0");
        assert_equal_double(0.0, obj->u.pl.normal.x, 0.001, "Plane normal X should be 0.0");
        assert_equal_double(1.0, obj->u.pl.normal.y, 0.001, "Plane normal Y should be 1.0");
        assert_equal_double(0.0, obj->u.pl.normal.z, 0.001, "Plane normal Z should be 0.0");
        assert_equal_int(0, obj->u.pl.color.r, "Plane color R should be 0");
        assert_equal_int(0, obj->u.pl.color.g, "Plane color G should be 0");
        assert_equal_int(225, obj->u.pl.color.b, "Plane color B should be 225");
    }
    
    // テストケース2: 別の値の平面
    ft_bzero(&scene, sizeof(t_scene));
    parse_plane(line2, &scene, &app);
    assert_true(scene.objs != NULL, "Scene should have an object after parsing plane");
    if (scene.objs)
    {
        t_obj *obj = scene.objs;
        assert_equal_int(OBJ_PLANE, obj->type, "Object type should be OBJ_PLANE");
        assert_equal_double(10.0, obj->u.pl.point.x, 0.001, "Plane position X should be 10.0");
        assert_equal_double(20.0, obj->u.pl.point.y, 0.001, "Plane position Y should be 20.0");
        assert_equal_double(30.0, obj->u.pl.point.z, 0.001, "Plane position Z should be 30.0");
        assert_equal_double(1.0, obj->u.pl.normal.x, 0.001, "Plane normal X should be 1.0");
        assert_equal_double(0.0, obj->u.pl.normal.y, 0.001, "Plane normal Y should be 0.0");
        assert_equal_double(0.0, obj->u.pl.normal.z, 0.001, "Plane normal Z should be 0.0");
        assert_equal_int(100, obj->u.pl.color.r, "Plane color R should be 100");
        assert_equal_int(150, obj->u.pl.color.g, "Plane color G should be 150");
        assert_equal_int(200, obj->u.pl.color.b, "Plane color B should be 200");
    }
    
    // 不正な入力のテストはexit_errmsgを使用しているため、ここではテストしない
    
    log_test_result("parse_plane", 1);
    cleanup_test();
}
