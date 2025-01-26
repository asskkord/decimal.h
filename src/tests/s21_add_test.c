#include "s21_main_tests.h"
// https://colab.research.google.com/drive/1GzBgM_rt14kOPGKEP0CnwZPIcwmhymkR?usp=sharing

START_TEST(s21_add_test_one) {
  s21_decimal val1 = {{0, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 0
  s21_decimal val2 = {{1, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 1
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 1
}
END_TEST

START_TEST(s21_add_test_one_minus) {
  s21_decimal val1 = {{0, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 0
  s21_decimal val2 = {{1, 0, 0, 0x80000000}};  // sign bit= 1 exponent= 0
  // 1
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);  // sign bit= 1 exponent= 0
  // 1
}
END_TEST

START_TEST(s21_add_test_1int) {
  s21_decimal val1 = {{14366534, 0, 0, 0x00020000}};  // sign bit= 0 exponent=
                                                      // -2
  // 143665.34
  s21_decimal val2 = {{576456, 0, 0, 0x00040000}};  // sign bit= 0 exponent= -4
  // 57.6456
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1437229856);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 262144);  // sign bit= 0 exponent= -4
  // 143722.9856
}
END_TEST

START_TEST(s21_add_test_3ints) {
  s21_decimal val1 = {{3550036140, 3631355950, 77886739,
                       0x000F0000}};  // sign bit= 0 exponent= -15
  // 1436756756665.367657457467564
  s21_decimal val2 = {
      {4230301616, 1342635, 0, 0x00090000}};  // sign bit= 0 exponent= -9
  // 5766577.645766576
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], (int)2897644716);
  ck_assert_int_eq(res.bits[1], (int)1942577246);
  ck_assert_int_eq(res.bits[2], 77887052);
  ck_assert_uint_eq(res.bits[3], 983040);  // sign bit= 0 exponent= -15
  // 1436762523243.013424033467564
}
END_TEST

START_TEST(s21_add_test_3ints_minus) {
  s21_decimal val1 = {{3550036140, 3631355950, 77886739,
                       0x000F0000}};  // sign bit= 0 exponent= -15
  // 1436756756665.367657457467564
  s21_decimal val2 = {
      {4230301616, 1342635, 0, 0x80090000}};  // sign bit= 1 exponent= -9
  // -5766577.645766576
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], (int)4202427564);
  ck_assert_int_eq(res.bits[1], 1025167358);
  ck_assert_int_eq(res.bits[2], 77886427);
  ck_assert_uint_eq(res.bits[3], 983040);  // sign bit= 0 exponent= -15
  // 1436750990087.721890881467564
}
END_TEST

START_TEST(s21_add_test_sub1int) {
  s21_decimal val1 = {{3550036140, 3631355950, 77886739,
                       0x000F0000}};  // sign bit= 0 exponent= -15
  // 1436756756665.367657457467564
  s21_decimal val2 = {
      {0XFFFFFFFF, 0, 0, 0x80060000}};  // sign bit= 1 exponent= -6
  // -4294.967295
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 255068844);
  ck_assert_int_eq(res.bits[1], (int)2631355951);
  ck_assert_int_eq(res.bits[2], 77886739);
  ck_assert_uint_eq(res.bits[3], 983040);  // sign bit= 0 exponent= -15
  // 1436756752370.400362457467564
}
END_TEST

START_TEST(s21_add_test_first_minus) {
  s21_decimal val1 = {
      {291, 1110, 1929, 0x800D0000}};  // sign bit= 1 exponent= -13
  // -3558376932.2953138766115
  s21_decimal val2 = {
      {2327839011, 3886551757, 302, 0x00100000}};  // sign bit= 0 exponent= -16
  // 558760.9322953138766115
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1967419285);
  ck_assert_int_eq(res.bits[1], 409525538);
  ck_assert_int_eq(res.bits[2], 1928697);
  ck_assert_uint_eq(res.bits[3], (int)2148532224);  // sign bit= 1 exponent= -16
  // -3557818171.3630185627348885
}
END_TEST

START_TEST(s21_add_test_second_minus) {
  s21_decimal val1 = {
      {2327839011, 3886551757, 302, 0x00100000}};  // sign bit= 0 exponent= -16
  // 558760.9322953138766115
  s21_decimal val2 = {
      {291, 1110, 1929, 0x800D0000}};  // sign bit= 1 exponent= -13
  // -3558376932.2953138766115
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1967419285);
  ck_assert_int_eq(res.bits[1], 409525538);
  ck_assert_int_eq(res.bits[2], 1928697);
  ck_assert_uint_eq(res.bits[3], (int)2148532224);  // sign bit= 1 exponent= -16
  // -3557818171.3630185627348885
}
END_TEST

START_TEST(s21_add_test_full_minus) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_fit) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF,
                       0x000F0000}};  // sign bit= 0 exponent= -15
  // 79228162514264.337593543950335
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF,
                       0x001C0000}};  // sign bit= 0 exponent= -28
  // 7.9228162514264337593543950335
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 174964493);
  ck_assert_int_eq(res.bits[1], (int)2577164845);
  ck_assert_int_eq(res.bits[2], 429496729);
  ck_assert_uint_eq(res.bits[3], 917504);  // sign bit= 0 exponent= -14
  // 79228162514272.26040979537677
}
END_TEST

START_TEST(s21_add_test_sub01) {
  s21_decimal val1 = {{2576980378, 2576980377, 429496729,
                       0x800E0000}};  // sign bit= 1 exponent= -14
  // -79228162514264.337593543950335
  s21_decimal val2 = {{1, 0, 0, 0x00010000}};  // sign bit= 0 exponent= -1
  // 0.1
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1260845466);
  ck_assert_int_eq(res.bits[1], (int)2576978049);
  ck_assert_int_eq(res.bits[2], 429496729);
  ck_assert_uint_eq(res.bits[3], (int)2148401152);  // sign bit= 1 exponent= -14
  // -79228162514264.23759354395034
}
END_TEST

START_TEST(s21_add_test_fit2) {
  s21_decimal val1 = {{2576980377, 2576980377, 429496729,
                       0x00000000}};  // sign bit= 0 exponent= 0
  // 7922816251426433759354395033
  s21_decimal val2 = {{8, 0, 0, 0x00010000}};  // sign bit= 0 exponent= -1
  // 0.8
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], (int)2576980378);
  ck_assert_int_eq(res.bits[1], (int)2576980377);
  ck_assert_int_eq(res.bits[2], 429496729);
  ck_assert_uint_eq(res.bits[3], 0);  // sign bit= 0 exponent= 0
  // 7922816251426433759354395034
}
END_TEST

START_TEST(s21_add_test_overflow) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(s21_add_test_overflow2) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF,
                       0x000F0000}};  // sign bit= 0 exponent= -15
  // 79228162514264.337593543950335
  s21_decimal val2 = {{1, 0, 0, 0x00010000}};  // sign bit= 0 exponent= -1
  // 0.1
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], (int)3893115290);
  ck_assert_int_eq(res.bits[1], (int)2576982705);
  ck_assert_int_eq(res.bits[2], 429496729);
  ck_assert_uint_eq(res.bits[3], 917504);  // sign bit= 0 exponent= -14
  // 79228162514264.43759354395034
}
END_TEST

START_TEST(s21_sub_test_4) {
  s21_decimal val1 = {{3550036140, 3631355950, 77886739,
                       0x000F0000}};  // sign bit= 0 exponent= -15
  // 1436756756665.367657457467564
  s21_decimal val2 = {
      {4294967295, 0, 0, 0x00060000}};  // sign bit= 1 exponent= -6
  // 4294.967295
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], (int)2550036140);
  ck_assert_int_eq(res.bits[1], 336388654);
  ck_assert_int_eq(res.bits[2], 77886740);
  ck_assert_uint_eq(res.bits[3], 983040);  // sign bit= 0 exponent= -15
  // 1436756760960.334952457467564
}
END_TEST

Suite *s21_add_suite() {
  Suite *s;
  TCase *tc_s21_add;
  s = suite_create("\033[34m \033[46m ADD TESTS \033[0m");
  tc_s21_add = tcase_create("s21_add");

  tcase_add_test(tc_s21_add, s21_add_test_one);
  tcase_add_test(tc_s21_add, s21_add_test_one_minus);
  tcase_add_test(tc_s21_add, s21_add_test_1int);
  tcase_add_test(tc_s21_add, s21_add_test_3ints);
  tcase_add_test(tc_s21_add, s21_add_test_3ints_minus);
  tcase_add_test(tc_s21_add, s21_add_test_sub1int);
  tcase_add_test(tc_s21_add, s21_add_test_first_minus);
  tcase_add_test(tc_s21_add, s21_add_test_second_minus);
  tcase_add_test(tc_s21_add, s21_add_test_full_minus);
  tcase_add_test(tc_s21_add, s21_add_test_fit);
  tcase_add_test(tc_s21_add, s21_add_test_sub01);
  tcase_add_test(tc_s21_add, s21_add_test_fit2);
  tcase_add_test(tc_s21_add, s21_add_test_overflow);
  tcase_add_test(tc_s21_add, s21_add_test_overflow2);
  tcase_add_test(tc_s21_add, s21_sub_test_4);

  suite_add_tcase(s, tc_s21_add);

  return s;
}