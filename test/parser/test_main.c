#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "test_app.h"
#include <assert.h>

#define TEST_FILE "../../maps/example.rt"

/* テストに必要な関数の宣言 */
t_list *xgc_init(t_app *app);
t_scene *parse_scene(char *filename, t_app *app);

/* ファイルの存在をチェックするヘルパー関数 */
bool file_exists(const char* path) {
    FILE* file = fopen(path, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

/* テスト用のアプリケーションコンテキストを初期化 */
static t_app *new_test_app(void)
{
    static t_app app;           /* 静的領域に確保すると楽 */
    memset(&app, 0, sizeof(app));
    app.gc = xgc_init(&app);
    return &app;
}

/* テストの結果を報告する関数 */
void test_report(const char* test_name, bool success, const char* message) {
    printf("[%s] %s: %s\n", 
           success ? "PASS" : "FAIL",
           test_name, 
           message ? message : "");
}

/* ファイル存在テスト */
void test_file_exists(void) {
    const char* example_path = TEST_FILE;
    printf("Checking file existence: %s\n", example_path);
    
    bool exists = file_exists(example_path);
    test_report("FileExists", exists, exists ? "File exists" : "File not found");
}

/* テスト環境用の関数宣言 */
int test_error_occurred(void);
char *test_get_error_msg(void);
void test_reset_error(void);

/* パーサーの基本機能テスト */
void test_parser_basic(void) {
    const char* example_path = TEST_FILE;
    if (!file_exists(example_path)) {
        test_report("ParserBasic", false, "Test file does not exist");
        return;
    }
    
    printf("Testing parser with file: %s\n", example_path);
    t_app *app = new_test_app();
    /* エラー状態をリセット */
    test_reset_error();
    
    /* パーサーを実行 */
    t_scene *sc = parse_scene((char*)example_path, app);
    
    /* エラーが発生したかチェック */
    if (test_error_occurred()) {
        char message[256];
        snprintf(message, sizeof(message), "Parser error: %s", test_get_error_msg());
        test_report("ParserBasic", false, message);
        return;
    }
    
    /* パーサーがエラーを返した場合 */
    if (sc == NULL) {
        test_report("ParserBasic", false, "Parser returned NULL");
        return;
    }
    
    /* シーン構造体の内容を出力 */
    print_scene(sc);
    
    /* パース結果の検証 */
    bool ambient_ok = sc->amb.ratio > 0.0;
    bool camera_ok = sc->cam.fov > 0.0;
    bool lights_ok = (sc->lights != NULL);
    bool objects_ok = (sc->objs   != NULL);
    
    bool all_ok = ambient_ok && camera_ok && lights_ok && objects_ok;
    
    char message[256];
    snprintf(message, sizeof(message),
             "Ambient: %s, Camera: %s, Lights: %s, Objects: %s",
             ambient_ok ? "OK" : "NG",
             camera_ok ? "OK" : "NG",
             lights_ok ? "OK" : "NG",
             objects_ok ? "OK" : "NG");
    test_report("ParserBasic", all_ok, message);

    print_scene(sc);
}

/* ベクトルを出力する関数 */
void print_vec3(const char* name, t_vec3 vec) {
    printf("  %s: (%.2f, %.2f, %.2f)\n", name, vec.x, vec.y, vec.z);
}

/* 色を出力する関数 */
void print_color(const char* name, t_color color) {
    printf("  %s: RGB(%d, %d, %d)\n", name, color.r, color.g, color.b);
}

/* 環境光を出力する関数 */
void print_ambient(t_ambient amb) {
    printf("Ambient Light:\n");
    printf("  Ratio: %.2f\n", amb.ratio);
    print_color("Color", amb.color);
}

/* カメラを出力する関数 */
void print_camera(t_camera cam) {
    printf("Camera:\n");
    print_vec3("Position", cam.pos);
    print_vec3("Direction", cam.dir);
    printf("  FOV: %.2f degrees\n", cam.fov);
}

/* 光源を出力する関数 */
static void print_lights(t_lights *lst)
{
    int idx = 0;
    for (t_lights *l = lst; l; l = l->next)
    {
        printf("Light %d:\n", ++idx);
        print_vec3("Position", l->pos);
        printf("  Brightness: %.2f\n", l->bright);
        print_color("Color", l->color);
    }
}

/* 球体を出力する関数 */
void print_sphere(t_sphere sp) {
    printf("  Sphere:\n");
    print_vec3("Center", sp.center);
    printf("    Radius: %.2f\n", sp.radius);
    print_color("Color", sp.color);
}

/* 平面を出力する関数 */
void print_plane(t_plane pl) {
    printf("  Plane:\n");
    print_vec3("Point", pl.point);
    print_vec3("Normal", pl.normal);
    print_color("Color", pl.color);
}

/* 円柱を出力する関数 */
void print_cylinder(t_cylinder cy) {
    printf("  Cylinder:\n");
    print_vec3("Center", cy.center);
    print_vec3("Axis", cy.axis);
    printf("    Radius: %.2f\n", cy.radius);
    printf("    Height: %.2f\n", cy.height);
    print_color("Color", cy.color);
}

/* オブジェクト種別名を取得 */
static const char* obj_type_name(t_obj_type t)
{
    switch (t) {
        case OBJ_SPHERE: return "Sphere";
        case OBJ_PLANE: return "Plane";
        case OBJ_CYLINDER: return "Cylinder";
        case OBJ_CONE: return "Cone";
        case OBJ_HYPERBOLOID: return "Hyperboloid";
        case OBJ_PARABOLOID: return "Paraboloid";
        default: return "Unknown";
    }
}

/* ──────────────────────────────── *
 *  印字ユーティリティ（新オブジェクト対応）
 * ──────────────────────────────── */
static void print_objects(t_obj *objs)
{
    int idx = 0;
    for (t_obj *o = objs; o; o = o->next)
    {
        printf("  [%d] %-12s\n", ++idx, obj_type_name(o->type));
        switch (o->type)
        {
            case OBJ_SPHERE:
                print_vec3("center", o->u.sp.center);
                printf("    radius: %.3f\n", o->u.sp.radius);
                break;
            case OBJ_PLANE:
                print_vec3("point",  o->u.pl.point);
                print_vec3("normal", o->u.pl.normal);
                break;
            case OBJ_CYLINDER:
                print_vec3("center", o->u.cy.center);
                print_vec3("axis",   o->u.cy.axis);
                printf("    r=%.3f h=%.3f\n", o->u.cy.radius, o->u.cy.height);
                break;
            case OBJ_CONE:
                print_vec3("vertex", o->u.co.vertex);
                print_vec3("axis",   o->u.co.axis);
                printf("    angle=%.3f h=%.3f\n", o->u.co.angle, o->u.co.height);
                break;
            case OBJ_HYPERBOLOID:
                print_vec3("center", o->u.hb.center);
                print_vec3("axis",   o->u.hb.axis);
                printf("    a=%.3f b=%.3f c=%.3f\n", o->u.hb.a, o->u.hb.b, o->u.hb.c);
                break;
            case OBJ_PARABOLOID:
                print_vec3("vertex", o->u.pb.vertex);
                print_vec3("axis",   o->u.pb.axis);
                printf("    k=%.3f h=%.3f\n", o->u.pb.k, o->u.pb.height);
                break;
            default:
                break;
        }
    }
}

/* シーン全体を出力する関数 */
void print_scene(t_scene *scene)
{
    if (!scene)
    {
        printf("Scene is NULL\n");
        return;
    }

    printf("\n=== Scene Contents ===\n");
    print_ambient(scene->amb);
    print_camera(scene->cam);
    print_lights(scene->lights);
    print_objects(scene->objs);
    printf("=====================\n\n");
}

/* メイン関数 */
int main(void) {
    printf("=== miniRT Parser Tests ===\n");
    
    /* ファイル存在テスト */
    test_file_exists();
    
    /* パーサーの基本機能テスト */
    test_parser_basic();
    
    printf("=== Tests Completed ===\n");
    return 0;
}