#include "test.h"

void test_parse_cylinder(void)
{
    t_app app;
    t_scene scene;
    char line1[] = " 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255";
    char line2[] = " 10,20,30 1,0,0 5.5 10.0 100,150,200";
    
    setup_test();
    fprintf(stdout, "\n----- Testing parse_cylinder -----\n");
    
    // 初期化
    ft_bzero(&app, sizeof(t_app));
    ft_bzero(&scene, sizeof(t_scene));
    
    // テストケース1: 標準的な円柱
    parse_cylinder(line1, &scene, &app);
    assert_true(scene.objs != NULL, "Scene should have an object after parsing cylinder");
    if (scene.objs)
    {
        t_obj *obj = scene.objs;
        assert_equal_int(OBJ_CYLINDER, obj->type, "Object type should be OBJ_CYLINDER");
        assert_equal_double(50.0, obj->u.cy.center.x, 0.001, "Cylinder position X should be 50.0");
        assert_equal_double(0.0, obj->u.cy.center.y, 0.001, "Cylinder position Y should be 0.0");
        assert_equal_double(20.6, obj->u.cy.center.z, 0.001, "Cylinder position Z should be 20.6");
        assert_equal_double(0.0, obj->u.cy.axis.x, 0.001, "Cylinder direction X should be 0.0");
        assert_equal_double(0.0, obj->u.cy.axis.y, 0.001, "Cylinder direction Y should be 0.0");
        assert_equal_double(1.0, obj->u.cy.axis.z, 0.001, "Cylinder direction Z should be 1.0");
        assert_equal_double(14.2, obj->u.cy.radius, 0.001, "Cylinder radius should be 14.2");
        assert_equal_double(21.42, obj->u.cy.height, 0.001, "Cylinder height should be 21.42");
        assert_equal_int(10, obj->u.cy.color.r, "Cylinder color R should be 10");
        assert_equal_int(0, obj->u.cy.color.g, "Cylinder color G should be 0");
        assert_equal_int(255, obj->u.cy.color.b, "Cylinder color B should be 255");
    }
    
    // テストケース2: 別の値の円柱
    ft_bzero(&scene, sizeof(t_scene));
    parse_cylinder(line2, &scene, &app);
    assert_true(scene.objs != NULL, "Scene should have an object after parsing cylinder");
    if (scene.objs)
    {
        t_obj *obj = scene.objs;
        assert_equal_int(OBJ_CYLINDER, obj->type, "Object type should be OBJ_CYLINDER");
        assert_equal_double(10.0, obj->u.cy.center.x, 0.001, "Cylinder position X should be 10.0");
        assert_equal_double(20.0, obj->u.cy.center.y, 0.001, "Cylinder position Y should be 20.0");
        assert_equal_double(30.0, obj->u.cy.center.z, 0.001, "Cylinder position Z should be 30.0");
        assert_equal_double(1.0, obj->u.cy.axis.x, 0.001, "Cylinder direction X should be 1.0");
        assert_equal_double(0.0, obj->u.cy.axis.y, 0.001, "Cylinder direction Y should be 0.0");
        assert_equal_double(0.0, obj->u.cy.axis.z, 0.001, "Cylinder direction Z should be 0.0");
        assert_equal_double(5.5, obj->u.cy.radius, 0.001, "Cylinder radius should be 5.5");
        assert_equal_double(10.0, obj->u.cy.height, 0.001, "Cylinder height should be 10.0");
        assert_equal_int(100, obj->u.cy.color.r, "Cylinder color R should be 100");
        assert_equal_int(150, obj->u.cy.color.g, "Cylinder color G should be 150");
        assert_equal_int(200, obj->u.cy.color.b, "Cylinder color B should be 200");
    }
    
    // 不正な入力のテストはexit_errmsgを使用しているため、ここではテストしない
    
    log_test_result("parse_cylinder", 1);
    cleanup_test();
}
