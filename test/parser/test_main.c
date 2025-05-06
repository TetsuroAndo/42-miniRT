#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "test_app.h"

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
    static t_app app; /* 静的領域なのでテスト間で毎回 0-clear */
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
    bool light_ok = sc->light.bright > 0.0;
    bool objects_ok = sc->objs != NULL;
    
    bool all_ok = ambient_ok && camera_ok && light_ok && objects_ok;
    
    char message[256];
    snprintf(message, sizeof(message), 
             "Ambient: %s, Camera: %s, Light: %s, Objects: %s",
             ambient_ok ? "OK" : "NG",
             camera_ok ? "OK" : "NG",
             light_ok ? "OK" : "NG",
             objects_ok ? "OK" : "NG");
    
    test_report("ParserBasic", all_ok, message);
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
void print_light(t_light light) {
    printf("Light:\n");
    print_vec3("Position", light.pos);
    printf("  Brightness: %.2f\n", light.bright);
    print_color("Color", light.color);
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

/* オブジェクトを出力する関数 */
void print_objects(t_obj *objs) {
    printf("Objects:\n");
    if (objs == NULL) {
        printf("  No objects\n");
        return;
    }
    
    int count = 0;
    t_obj *current = objs;
    while (current) {
        count++;
        printf("Object %d:\n", count);
        
        switch (current->type) {
            case OBJ_SPHERE:
                print_sphere(current->u.sp);
                break;
            case OBJ_PLANE:
                print_plane(current->u.pl);
                break;
            case OBJ_CYLINDER:
                print_cylinder(current->u.cy);
                break;
            default:
                printf("  Unknown object type\n");
        }
        
        current = current->next;
    }
}

/* シーン全体を出力する関数 */
void print_scene(t_scene *scene) {
    if (scene == NULL) {
        printf("Scene is NULL\n");
        return;
    }
    
    printf("\n=== Scene Contents ===\n");
    print_ambient(scene->amb);
    print_camera(scene->cam);
    print_light(scene->light);
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