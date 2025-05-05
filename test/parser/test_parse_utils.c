#include "test.h"

void test_parse_utils(void)
{
    t_app app;
    double out_d;
    t_color out_c;
    t_vec3 out_v;
    char *s1, *s2, *s3, *s4, *s5;
    
    setup_test();
    fprintf(stdout, "\n----- Testing parse utilities -----\n");
    
    // 初期化
    ft_bzero(&app, sizeof(t_app));
    
    // parse_f64のテスト
    s1 = ft_strdup("42.5 ");
    assert_true(parse_f64(&s1, &out_d, -100.0, 100.0), "parse_f64 should return true for valid input");
    assert_equal_double(42.5, out_d, 0.001, "parse_f64 should parse 42.5 correctly");
    assert_equal_int(' ', *s1, "parse_f64 should advance the pointer to the next character");
    free(s1);
    
    // parse_rgbのテスト
    s2 = ft_strdup("255,128,64 ");
    assert_true(parse_rgb(&s2, &out_c), "parse_rgb should return true for valid input");
    assert_equal_int(255, out_c.r, "parse_rgb should parse R=255 correctly");
    assert_equal_int(128, out_c.g, "parse_rgb should parse G=128 correctly");
    assert_equal_int(64, out_c.b, "parse_rgb should parse B=64 correctly");
    assert_equal_int(' ', *s2, "parse_rgb should advance the pointer to the next character");
    free(s2);
    
    // parse_vec3のテスト
    s3 = ft_strdup("1.0,2.0,3.0 ");
    assert_true(parse_vec3(&s3, &out_v), "parse_vec3 should return true for valid input");
    assert_equal_double(1.0, out_v.x, 0.001, "parse_vec3 should parse x=1.0 correctly");
    assert_equal_double(2.0, out_v.y, 0.001, "parse_vec3 should parse y=2.0 correctly");
    assert_equal_double(3.0, out_v.z, 0.001, "parse_vec3 should parse z=3.0 correctly");
    assert_equal_int(' ', *s3, "parse_vec3 should advance the pointer to the next character");
    free(s3);
    
    // parse_normal_vec3のテスト
    s4 = ft_strdup("0.0,1.0,0.0 ");
    assert_true(parse_normal_vec3(&s4, &out_v), "parse_normal_vec3 should return true for valid input");
    assert_equal_double(0.0, out_v.x, 0.001, "parse_normal_vec3 should parse x=0.0 correctly");
    assert_equal_double(1.0, out_v.y, 0.001, "parse_normal_vec3 should parse y=1.0 correctly");
    assert_equal_double(0.0, out_v.z, 0.001, "parse_normal_vec3 should parse z=0.0 correctly");
    assert_equal_int(' ', *s4, "parse_normal_vec3 should advance the pointer to the next character");
    free(s4);
    
    // expect_line_endのテスト
    s5 = ft_strdup(" \t\n");
    assert_true(expect_line_end(&s5), "expect_line_end should return true for whitespace and newline");
    free(s5);
    
    log_test_result("parse_utils", 1);
    cleanup_test();
}
