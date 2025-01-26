#include "s21_main_tests.h"

//  decimal python3 для тестов
// https://colab.research.google.com/drive/1UPoxg3coZP3mjTfGeUEZvk7Jl6kx1x5O?usp=sharing

START_TEST(s21_mul_test_simple) {
  s21_decimal val1 = {{1, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 1
  s21_decimal val2 = {{0, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 0
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 0
}
END_TEST

START_TEST(s21_mul_test_simple2) {
  s21_decimal val1 = {{1, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 1
  s21_decimal val2 = {{1, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 1
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 1
}
END_TEST

START_TEST(s21_mul_test_exp) {
  s21_decimal val1 = {{1, 0, 0, 0x00010000}};  // sign bit= 0 exponent= -1
  // 0.1
  s21_decimal val2 = {{2, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 2
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 2);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 65536);  // sign bit= 0 exponent= -1
  // 0.2
}
END_TEST

START_TEST(s21_mul_test_exp_max) {
  s21_decimal val1 = {{1, 0, 0, 0b00000000011111111000000000000000}};
  s21_decimal val2 = {{1, 0, 0, 0b00000000011111111000000000000000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_sign) {
  s21_decimal val1 = {
      {2147483647, 0, 0, 0x00060000}};  // sign bit= 0 exponent= -6
  // 2147.483647
  s21_decimal val2 = {{5765875, 0, 0, 0x80000000}};  // sign bit= 1 exponent= 0
  // -5765875
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 2141717773);
  ck_assert_int_eq(res.bits[1], 2882937);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2147876864);  // sign bit= -6 exponent= 1
  // -12382122273.146125
}
END_TEST

START_TEST(s21_mul_test_big_first) {
  s21_decimal val1 = {{12345678, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 12345678
  s21_decimal val2 = {{12345678, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 12345678
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 260846532);
  ck_assert_int_eq(res.bits[1], 35487);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 152415765279684
}
END_TEST

START_TEST(s21_mul_test_big_first2) {
  s21_decimal val1 = {
      {1912277059, 287, 0, 0x000F0000}};  // sign bit= -15 exponent= 0
  // 0.001234567891011
  s21_decimal val2 = {{10, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 10
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1942901406);
  ck_assert_int_eq(res.bits[1], 2874);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 983040);  // sign bit= -15 exponent= 0
  // 0.012345678910110
}
END_TEST

START_TEST(s21_mul_test_big_first3) {
  s21_decimal val1 = {
      {2147483647, 0, 0, 0x00060000}};  // sign bit= 0 exponent= -6
  // 2147.483647
  s21_decimal val2 = {
      {2147483647, 0, 0, 0x00020000}};  // sign bit= 0 exponent= -2
  // 21474836.47
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 1073741823);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 524288);  // sign bit= -8 exponent= 0
  // 46116860141.32420609
}
END_TEST

START_TEST(s21_mul_test_big_first4) {
  s21_decimal val1 = {
      {2147483647, 0, 0, 0x00060000}};  // sign bit= 0 exponent= -6
  // 2147.483647
  s21_decimal val2 = {
      {4294957296, 4999, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 21474836470000
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 10000);
  ck_assert_int_eq(res.bits[1], (int)4294957296);
  ck_assert_int_eq(res.bits[2], 2499);
  ck_assert_uint_eq(res.bits[3], 393216);  // sign bit= -6 exponent= 0
  // 46116860141324206.090000
}
END_TEST

START_TEST(s21_mul_test_big_second) {
  s21_decimal val1 = {
      {4294967295, 4294967295, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 18446744073709551615
  s21_decimal val2 = {{8, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 8
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], (int)4294967288);
  ck_assert_int_eq(res.bits[1], (int)4294967295);
  ck_assert_int_eq(res.bits[2], 7);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 147573952589676412920
}
END_TEST

START_TEST(s21_mul_test_big_second2) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0, 0}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_big_third) {
  s21_decimal val1 = {
      {0, 2208410624, 1526457626, 0x00000000}};  // sign bit= 0 exponent= 0
  // 7.9228163E+28
  s21_decimal val2 = {{1, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 1
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], (int)2208410624);
  ck_assert_int_eq(res.bits[2], 1526457626);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 7.9228163E+28
}
END_TEST

START_TEST(s21_mul_test_max) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_min) {
  s21_decimal val1 = {
      {0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0b10000000000011100000000000000000}};
  s21_decimal val2 = {
      {0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0b10000000000011100000000000000000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(s21_mul_test_ten) {
  s21_decimal val1 = {{123, 123, 123, 0X00000000}};
  s21_decimal val2 = {{10, 0, 0, 0X00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1230);
  ck_assert_int_eq(res.bits[1], 1230);
  ck_assert_int_eq(res.bits[2], 1230);
  ck_assert_int_eq(res.bits[3], 0X00000000);
}
END_TEST

START_TEST(s21_mul_test_random) {
  s21_decimal val1 = {
      {1749644830, 1844674, 0, 0x80000000}};  // sign bit= 1 exponent= 0
  // -7922816251426334
  s21_decimal val2 = {{1, 0, 0, 0x00090000}};  // sign bit= 0 exponent= -9
  // 1E-9
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1749644830);
  ck_assert_int_eq(res.bits[1], 1844674);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2148073472);  // sign bit= 1 exponent= -9
  // -7922816.251426334
}
END_TEST

START_TEST(s21_mul_test_random2) {
  s21_decimal val1 = {
      {4221068376, 2038325, 0, 0x00100000}};  // sign bit= 0 exponent= -16
  // 0.8754543434687576
  s21_decimal val2 = {{1, 0, 0, 0x00070000}};  // sign bit= 0 exponent= -7
  // 1E-7
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], (int)4221068376);
  ck_assert_int_eq(res.bits[1], 2038325);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 1507328);  // sign bit= 0 exponent= -23
  // 8.754543434687576E-8
}
END_TEST

START_TEST(s21_mul_test_max_fit) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0}};
  s21_decimal val2 = {{1, 0, 0, 0x00070000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], (int)4294967295);
  ck_assert_int_eq(res.bits[1], (int)4294967295);
  ck_assert_int_eq(res.bits[2], (int)4294967295);
  ck_assert_uint_eq(res.bits[3], 458752);
}
END_TEST

START_TEST(s21_mul_test_div0) {
  s21_decimal val1 = {
      {2808348672, 232830643, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 1000000000000000000
  s21_decimal val2 = {{0, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 0
  s21_decimal res;
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 0
}
END_TEST

Suite *s21_mul_suite() {
  Suite *s;
  TCase *tc_s21_mul;
  s = suite_create("\033[34m \033[46m Multiplication TESTS \033[0m");
  tc_s21_mul = tcase_create("s21_mul");
  tcase_add_test(tc_s21_mul, s21_mul_test_simple);
  tcase_add_test(tc_s21_mul, s21_mul_test_simple2);
  tcase_add_test(tc_s21_mul, s21_mul_test_exp);
  tcase_add_test(tc_s21_mul, s21_mul_test_exp_max);
  tcase_add_test(tc_s21_mul, s21_mul_test_sign);
  tcase_add_test(tc_s21_mul, s21_mul_test_big_first);
  tcase_add_test(tc_s21_mul, s21_mul_test_big_first2);
  tcase_add_test(tc_s21_mul, s21_mul_test_big_first3);
  tcase_add_test(tc_s21_mul, s21_mul_test_big_first4);
  tcase_add_test(tc_s21_mul, s21_mul_test_big_second);
  tcase_add_test(tc_s21_mul, s21_mul_test_big_second2);
  tcase_add_test(tc_s21_mul, s21_mul_test_big_third);
  tcase_add_test(tc_s21_mul, s21_mul_test_max);
  tcase_add_test(tc_s21_mul, s21_mul_test_min);
  tcase_add_test(tc_s21_mul, s21_mul_test_ten);
  tcase_add_test(tc_s21_mul, s21_mul_test_random);
  tcase_add_test(tc_s21_mul, s21_mul_test_random2);
  tcase_add_test(tc_s21_mul, s21_mul_test_max_fit);
  tcase_add_test(tc_s21_mul, s21_mul_test_div0);

  suite_add_tcase(s, tc_s21_mul);

  return s;
}
