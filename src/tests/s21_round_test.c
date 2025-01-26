#include "s21_main_tests.h"

// https://colab.research.google.com/drive/1wnlny2Hz6YeO7TtsQ1b6yzbc8e3_XUNS?usp=sharing

START_TEST(s21_round_test) {
  s21_decimal val1 = {{4294967285, 4294967295, 4294967295,
                       0x00010000}};  // sign bit= 0 exponent= -1
  // 7922816251426433759354395032.5
  s21_decimal res;
  ck_assert_int_eq(0, s21_round(val1, &res));
  ck_assert_int_eq(res.bits[0], (int)2576980377);
  ck_assert_int_eq(res.bits[1], (int)2576980377);
  ck_assert_int_eq(res.bits[2], 429496729);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 7922816251426433759354395032
}
END_TEST

START_TEST(s21_round_test2) {
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00010000}};  // sign bit= 0 exponent= -1
  // 7922816251426433759354395033.5
  s21_decimal res;
  ck_assert_int_eq(0, s21_round(val1, &res));
  ck_assert_int_eq(res.bits[0], (int)2576980378);
  ck_assert_int_eq(res.bits[1], (int)2576980377);
  ck_assert_int_eq(res.bits[2], 429496729);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 7922816251426433759354395034
}
END_TEST

START_TEST(s21_round_test3) {
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x80010000}};  // sign bit= 1 exponent= -1
  // -7922816251426433759354395033.5
  s21_decimal res;
  ck_assert_int_eq(0, s21_round(val1, &res));
  ck_assert_int_eq(res.bits[0], (int)2576980378);
  ck_assert_int_eq(res.bits[1], (int)2576980377);
  ck_assert_int_eq(res.bits[2], 429496729);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);  // sign bit= 1 exponent= 0
  // -7922816251426433759354395034
}
END_TEST

START_TEST(s21_round_test4) {
  s21_decimal val1 = {{2576980377, 2576980377, 429496729,
                       0x800C0000}};  // sign bit= 1 exponent= -12
  // -7922816251426433.7593543950334
  s21_decimal res;
  ck_assert_int_eq(0, s21_round(val1, &res));
  ck_assert_int_eq(res.bits[0], 1749644930);
  ck_assert_int_eq(res.bits[1], 1844674);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);  // sign bit= 1 exponent= 0
  // -7922816251426434
}
END_TEST

START_TEST(s21_round_test5) {
  s21_decimal val1 = {{1, 0, 0, 0x80010000}};  // sign bit= 1 exponent= -1
  // -0.1
  s21_decimal res;
  ck_assert_int_eq(0, s21_round(val1, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);  // sign bit= 0 exponent= 0
  // 0
}
END_TEST

START_TEST(s21_round_test6) {
  s21_decimal val1 = {{0, 0, 0, 0x80010000}};  // sign bit= 1 exponent= -1
  // -0.0
  s21_decimal res;
  ck_assert_int_eq(0, s21_round(val1, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);  // sign bit= 0 exponent= 0
  // 0
}
END_TEST

START_TEST(s21_round_test7) {
  s21_decimal val1 = {{4294967295, 4294967295, 4294967295,
                       0x00000000}};  // sign bit= 0 exponent= 0
  // 79228162514264337593543950335
  s21_decimal res;
  ck_assert_int_eq(0, s21_round(val1, &res));
  ck_assert_int_eq(res.bits[0], (int)4294967295);
  ck_assert_int_eq(res.bits[1], (int)4294967295);
  ck_assert_int_eq(res.bits[2], (int)4294967295);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 79228162514264337593543950335
}
END_TEST

START_TEST(s21_round_test8) {
  s21_decimal val1 = {
      {111111111, 0, 0, 0x00050000}};  // sign bit= 0 exponent= -5
  // 1111.11111
  s21_decimal res;
  ck_assert_int_eq(0, s21_round(val1, &res));
  ck_assert_int_eq(res.bits[0], 1111);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 1111
}
END_TEST

START_TEST(s21_round_test9) {
  s21_decimal val1 = {
      {3806854143, 353144138, 60263, 0x00090000}};  // sign bit= 0 exponent= -9
  // 1111657654856485.999999999
  s21_decimal res;
  ck_assert_int_eq(0, s21_round(val1, &res));
  ck_assert_int_eq(res.bits[0], (int)4154534694);
  ck_assert_int_eq(res.bits[1], 258827);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 1111657654856486
}
END_TEST

START_TEST(s21_round_test10) {
  s21_decimal val1 = {
      {4238200163, 1129929542, 60, 0x00060000}};  // sign bit= 0 exponent= -6
  // 1111657654856485.555555
  s21_decimal res;
  ck_assert_int_eq(0, s21_round(val1, &res));
  ck_assert_int_eq(res.bits[0], (int)4154534694);
  ck_assert_int_eq(res.bits[1], 258827);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 1111657654856486
}
END_TEST

Suite *s21_round_suite(void) {
  Suite *s = suite_create("\033[34m \033[46m ROUND TESTS \033[0m");
  TCase *tc = tcase_create("s21_round");

  tcase_add_test(tc, s21_round_test);
  tcase_add_test(tc, s21_round_test2);
  tcase_add_test(tc, s21_round_test3);
  tcase_add_test(tc, s21_round_test4);
  tcase_add_test(tc, s21_round_test5);
  tcase_add_test(tc, s21_round_test6);
  tcase_add_test(tc, s21_round_test7);
  tcase_add_test(tc, s21_round_test8);
  tcase_add_test(tc, s21_round_test9);
  tcase_add_test(tc, s21_round_test10);

  suite_add_tcase(s, tc);
  return s;
}