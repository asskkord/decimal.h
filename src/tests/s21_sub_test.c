#include "s21_main_tests.h"

// https://colab.research.google.com/drive/1Dw3CzxE2TDA5VzjsSnqmwUIiz3aFKVX8?usp=sharing

START_TEST(s21_sub_test_0) {
  s21_decimal val1 = {{0, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 0
  s21_decimal val2 = {{1, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 1
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);  // sign bit= 1 exponent= 0
  // -1
}
END_TEST

START_TEST(s21_sub_test_1) {
  s21_decimal val1 = {{345665, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 345665
  s21_decimal val2 = {{6767, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 6767
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 338898);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 338898
}
END_TEST

START_TEST(s21_sub_test_2) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_sub_test_3) {
  s21_decimal val1 = {{4294967236, 4294967295, 4294967295,
                       0x80000000}};  // sign bit= 1 exponent= 1
  // -79228162514264337593543950334
  s21_decimal val2 = {{4294967236, 4294967295, 4294967295,
                       0x80000000}};  // sign bit= 1 exponent= 1
  // -79228162514264337593543950334
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 0
}
END_TEST

START_TEST(s21_sub_test_4) {
  s21_decimal val1 = {{3550036140, 3631355950, 77886739,
                       0x000F0000}};  // sign bit= 0 exponent= -15
  // 1436756756665.367657457467564
  s21_decimal val2 = {
      {0XFFFFFFFF, 0, 0, 0x00060000}};  // sign bit= 0 exponent= -6
  // 4294.967295
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 255068844);
  ck_assert_int_eq(res.bits[1], (int)2631355951);
  ck_assert_int_eq(res.bits[2], 77886739);
  ck_assert_uint_eq(res.bits[3], 983040);  // sign bit= 0 exponent= -15
  // 1436756752370.400362457467564
}
END_TEST

START_TEST(s21_sub_test_5) {
  s21_decimal val1 = {{3550036140, 3631355950, 77886739,
                       0x000F0000}};  // sign bit= 0 exponent= -15
  // 1436756756665.367657457467564
  s21_decimal val2 = {
      {4294967295, 0, 0, 0x80060000}};  // sign bit= 1 exponent= -6
  // -4294.967295
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], (int)2550036140);
  ck_assert_int_eq(res.bits[1], 336388654);
  ck_assert_int_eq(res.bits[2], 77886740);
  ck_assert_uint_eq(res.bits[3], 983040);  // sign bit= 0 exponent= -15
  // 1436756760960.334952457467564
}
END_TEST

START_TEST(s21_sub_test_6) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x001C0000}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(s21_sub_test_7) {
  s21_decimal val1 = {
      {3835611545, 2890341199, 42949, 0x80090000}};  // sign bit= 1 exponent= -9
  // -792281625142679.354395033
  s21_decimal val2 = {{79, 0, 0, 0x80000000}};  // sign bit= 1 exponent= 0
  // -79
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 2145022873);
  ck_assert_int_eq(res.bits[1], (int)2890341181);
  ck_assert_int_eq(res.bits[2], 42949);
  ck_assert_uint_eq(res.bits[3], (int)2148073472);  // sign bit= 1 exponent= -9
  // -792281625142600.354395033
}
END_TEST

START_TEST(s21_sub_test_8) {
  s21_decimal val1 = {{0, 0, 1, 0x00000000}};
  s21_decimal val2 = {{1, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], (int)4294967295);
  ck_assert_int_eq(res.bits[1], (int)4294967295);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_sub_test_9) {
  s21_decimal val1 = {{100, 200, 300, 0x00050000}};  // sign bit= 0 exponent= -5
  // 55340232229718589.44100
  s21_decimal val2 = {
      {4294967295, 0, 0, 0x00060000}};  // sign bit= 0 exponent= -6
  // 4294.967295
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1001);
  ck_assert_int_eq(res.bits[1], 1999);
  ck_assert_int_eq(res.bits[2], 3000);
  ck_assert_uint_eq(res.bits[3], 393216);  // sign bit= 0 exponent= -6
  // 55340232229714294.473705
}
END_TEST

START_TEST(s21_sub_test_10) {
  s21_decimal val1 = {
      {3292292708, 1999552, 3000000, 0x00050000}};  // sign bit= 0 exponent= -5
  // 553402322297166685869.44100
  s21_decimal val2 = {
      {4294967295, 0, 0, 0x80060000}};  // sign bit= 1 exponent= -6
  // -4294.967295
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], (int)2858156007);
  ck_assert_int_eq(res.bits[1], 19995528);
  ck_assert_int_eq(res.bits[2], 30000000);
  ck_assert_uint_eq(res.bits[3], 393216);  // sign bit= 0 exponent= -6
  // 553402322297166690164.408295
}
END_TEST

START_TEST(s21_sub_test_11) {
  s21_decimal val1 = {{2333897159, 2320440798, 602334,
                       0x000C0000}};  // sign bit= 0 exponent= -12
  // 11111111111111.111111111111
  s21_decimal val2 = {{11, 0, 0, 0x80010000}};  // sign bit= 1 exponent= -1
  // -1.1
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], (int)2822269383);
  ck_assert_int_eq(res.bits[1], (int)2320441054);
  ck_assert_int_eq(res.bits[2], 602334);
  ck_assert_uint_eq(res.bits[3], 786432);  // sign bit= 0 exponent= -12
  // 11111111111112.211111111111
}
END_TEST

// START_TEST(s21_add_3_test_) {
//   s21_decimal val1 = {{100, 200, 300, 0x00050000}};

//   s21_decimal val2 = {{0XFFFFFFFF, 0, 0, 0x00060000}};
//   s21_decimal res;
//   ck_assert_int_eq(0, s21_sub(val1, val2, &res));
//   ck_assert_int_eq(res.bits[0], 1001);
//   ck_assert_int_eq(res.bits[1], 1999);
//   ck_assert_int_eq(res.bits[2], 3000);
//   ck_assert_int_eq(res.bits[3], 393216);
// }
// END_TEST

Suite *s21_sub_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("\033[34m \033[46m SUBSTRACTION TESTS \033[0m");
  tc = tcase_create("s21_sub_test");

  // tcase_add_test(tc, s21_add_3_test_);

  tcase_add_test(tc, s21_sub_test_0);
  tcase_add_test(tc, s21_sub_test_1);
  tcase_add_test(tc, s21_sub_test_2);
  tcase_add_test(tc, s21_sub_test_3);
  tcase_add_test(tc, s21_sub_test_4);
  tcase_add_test(tc, s21_sub_test_5);
  tcase_add_test(tc, s21_sub_test_6);
  tcase_add_test(tc, s21_sub_test_7);
  tcase_add_test(tc, s21_sub_test_8);
  tcase_add_test(tc, s21_sub_test_9);
  tcase_add_test(tc, s21_sub_test_10);
  tcase_add_test(tc, s21_sub_test_11);
  suite_add_tcase(s, tc);
  return s;
}