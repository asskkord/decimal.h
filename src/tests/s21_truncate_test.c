#include "s21_main_tests.h"

// https://colab.research.google.com/drive/1rbYX5kRFHWU85C8uNjjBMBPpJSA5Vehu?usp=sharing

START_TEST(s21_truncate_test) {
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                       0x00030000}};  // sign bit= 0 exponent= -3
  // 0xFFFFFFFF , 0xFFFFFFFF , 0xFFFFFFFF
  // 79228162514264337593543950.335
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], (int)2645699854);
  ck_assert_int_eq(res.bits[1], 1271310319);
  ck_assert_int_eq(res.bits[2], 4294967);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0
  // 79228162514264337593543950
}
END_TEST

START_TEST(s21_truncate_test2) {
  s21_decimal val1 = {{2576980378, 2576980377, 429496729,
                       0x80020000}};  // sign bit= 1 exponent= -2
  // 0x9999999A , 0x99999999 , 0x19999999
  // -79228162514264337593543950.335
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], (int)2645699854);
  ck_assert_int_eq(res.bits[1], 1271310319);
  ck_assert_int_eq(res.bits[2], 4294967);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);  // sign bit= 1
  // 79228162514264337593543950
}
END_TEST

START_TEST(s21_truncate_test3) {
  s21_decimal val1 = {{11, 0, 0, 0x00010000}};  // sign bit= 0 exponent= -1
  // 1.1
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0
  // 1
}
END_TEST

START_TEST(s21_truncate_test4) {
  s21_decimal val1 = {
      {4092717806, 360108, 0, 0x00090000}};  // sign bit= 0 exponent= -9
  // 1546656.175745774
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], 1546656);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0
  // 1546656
}
END_TEST

START_TEST(s21_truncate_test5) {
  s21_decimal val1 = {{0, 0, 0, 0x80030000}};  // sign bit= 1 exponent= -3
  // -0.000
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);  // sign bit= 1
  // 0
}
END_TEST

START_TEST(s21_truncate_test6) {
  s21_decimal val1 = {
      {1579388472, 2069605721, 0, 0x80090000}};  // sign bit= 1 exponent= -9
  // -8888888888.888888888
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], 298954296);
  ck_assert_int_eq(res.bits[1], 2);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);  // sign bit= 1
  // 8888888888
}
END_TEST

START_TEST(s21_truncate_test7) {
  s21_decimal val1 = {{2033164565, 2043353280, 66926059,
                       0x80090000}};  // sign bit= 1 exponent= -9
  // -1234567891011121314.123456789101112134444444444
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], (int)3000119458);
  ck_assert_int_eq(res.bits[1], 287445236);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);  // sign bit= 1
  // 1234567891011121314
}
END_TEST

START_TEST(s21_truncate_test8) {
  s21_decimal val1 = {{0, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 0x00000000 , 0x00000000 , 0x00000000
  // 0
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0
  // 0
}
END_TEST

START_TEST(s21_truncate_test9) {
  s21_decimal val1 = {{589056, 0, 0, 0x00060000}};  // sign bit= 0 exponent= -6
  // 0.589056
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0
  // 0
}
END_TEST

START_TEST(s21_truncate_test10) {
  s21_decimal val1 = {{3339419008, 3674760961, 1662408222,
                       0x00230000}};  // sign bit= 0 exponent= -35
  // 1.11111111111111111111111111111111111
  s21_decimal res;
  ck_assert_int_eq(1, s21_truncate(val1, &res));
}
END_TEST

Suite *s21_truncate_suite(void) {
  Suite *s = suite_create("\033[34m \033[46m TRUNCATE TESTS \033[0m");
  TCase *tc = tcase_create("s21_truncate");

  tcase_add_test(tc, s21_truncate_test);
  tcase_add_test(tc, s21_truncate_test2);
  tcase_add_test(tc, s21_truncate_test3);
  tcase_add_test(tc, s21_truncate_test4);
  tcase_add_test(tc, s21_truncate_test5);
  tcase_add_test(tc, s21_truncate_test6);
  tcase_add_test(tc, s21_truncate_test7);
  tcase_add_test(tc, s21_truncate_test8);
  tcase_add_test(tc, s21_truncate_test9);
  tcase_add_test(tc, s21_truncate_test10);

  suite_add_tcase(s, tc);
  return s;
}