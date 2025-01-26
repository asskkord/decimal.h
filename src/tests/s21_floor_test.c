#include "s21_main_tests.h"

// https://colab.research.google.com/drive/1uKkR-jp3c2dq62uNYYpjNg_JSXV_pFo4#scrollTo=j2vQ3krh0Kbb

START_TEST(s21_floor_test) {
  s21_decimal number = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_floor(number, &res));
  ck_assert_int_eq(res.bits[0], (int)4294967295);
  ck_assert_int_eq(res.bits[1], (int)4294967295);
  ck_assert_int_eq(res.bits[2], (int)4294967295);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_floor_test2) {
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00010000}};  // sign bit= 0 exponent= -1
  // 7922816251426433759354395033.5
  s21_decimal res;
  ck_assert_int_eq(0, s21_floor(val1, &res));
  ck_assert_int_eq(res.bits[0], (int)2576980377);
  ck_assert_int_eq(res.bits[1], (int)2576980377);
  ck_assert_int_eq(res.bits[2], 429496729);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0
}
END_TEST

START_TEST(s21_floor_test3) {
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x80010000}};  // sign bit= 1 exponent= 0
  // -7922816251426433759354395033.5
  s21_decimal res;
  ck_assert_int_eq(0, s21_floor(val1, &res));
  ck_assert_int_eq(res.bits[0], (int)2576980378);
  ck_assert_int_eq(res.bits[1], (int)2576980377);
  ck_assert_int_eq(res.bits[2], 429496729);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);  // sign bit= 1
}
END_TEST

START_TEST(s21_floor_test4) {
  s21_decimal val1 = {{5, 0, 0, 0x00010000}};  // sign bit= 0 exponent= -1
  // 0.5
  s21_decimal res;
  ck_assert_int_eq(0, s21_floor(val1, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0
}
END_TEST

START_TEST(s21_floor_test5) {
  s21_decimal val1 = {{2995627887, 2152600949, 350015446,
                       0x000E0000}};  // sign bit= 0 exponent= -14
  // 64566453634526.56263623452527
  s21_decimal res;
  ck_assert_int_eq(0, s21_floor(val1, &res));
  ck_assert_int_eq(res.bits[0], 210273758);
  ck_assert_int_eq(res.bits[1], 15033);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0
}
END_TEST

START_TEST(s21_floor_test6) {
  s21_decimal val1 = {{1, 0, 0, 0x00140000}};  // sign bit= 0 exponent= -20
  // 1E-20
  s21_decimal res;
  ck_assert_int_eq(0, s21_floor(val1, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0
}
END_TEST

START_TEST(s21_floor_test7) {
  s21_decimal val1 = {{0, 0, 0, 0x80000000}};  // sign bit= 1 exponent= 0
  // -0
  s21_decimal res;
  ck_assert_int_eq(0, s21_floor(val1, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);  // sign bit= 0
}
END_TEST

START_TEST(s21_floor_test8) {
  s21_decimal val1 = {{1, 0, 0, 0x80000000}};  // sign bit= 1 exponent= 0
  // -1
  s21_decimal res;
  ck_assert_int_eq(0, s21_floor(val1, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);  // sign bit= 1 exponent= 0
}
END_TEST

START_TEST(s21_floor_test9) {
  s21_decimal val1 = {
      {30716359, 2587, 0, 0x000D0000}};  // sign bit= 0 exponent= -13
  // 1.1111111111111
  s21_decimal res;
  ck_assert_int_eq(0, s21_floor(val1, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
}
END_TEST

Suite *s21_floor_suite(void) {
  Suite *s = suite_create("\033[34m \033[46m FLOOR TESTS \033[0m");
  TCase *tc = tcase_create("s21_floor");

  tcase_add_test(tc, s21_floor_test);
  tcase_add_test(tc, s21_floor_test2);
  tcase_add_test(tc, s21_floor_test3);
  tcase_add_test(tc, s21_floor_test4);
  tcase_add_test(tc, s21_floor_test5);
  tcase_add_test(tc, s21_floor_test6);
  tcase_add_test(tc, s21_floor_test7);
  tcase_add_test(tc, s21_floor_test8);
  tcase_add_test(tc, s21_floor_test9);
  suite_add_tcase(s, tc);
  return s;
}