#include "s21_main_tests.h"

START_TEST(test_s21_from_int_to_decimal_zero) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(0, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_positive) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(123, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], 123);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_negative) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(-456, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], 456);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], (int)2147483648);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_max_int) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(INT_MAX, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], INT_MAX);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_min_int) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(INT_MIN, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], (int)2147483648);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], (int)2147483648);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_out_of_range_high) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(INT_MAX, &val);
  ck_assert_int_eq(result, 0);

  result = s21_from_int_to_decimal(INT_MAX - 1, &val);
  ck_assert_int_eq(result, 0);

  result = s21_from_int_to_decimal(INT_MAX / 2, &val);
  ck_assert_int_eq(result, 0);

  result = s21_from_int_to_decimal(INT_MAX / 3, &val);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_out_of_range_low) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(INT_MIN, &val);
  ck_assert_int_eq(result, 0);

  result = s21_from_int_to_decimal(INT_MIN + 1, &val);
  ck_assert_int_eq(result, 0);

  result = s21_from_int_to_decimal(INT_MIN / 2, &val);
  ck_assert_int_eq(result, 0);

  result = s21_from_int_to_decimal(INT_MIN / 3, &val);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_positive_large) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(987654321, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], 987654321);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_negative_large) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(-987654321, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], 987654321);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], (int)2147483648);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_max_abs) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(INT_MAX - 1, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], INT_MAX - 1);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_min_abs) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(INT_MIN + 1, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], INT_MAX);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], (int)2147483648);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_max_value) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(INT_MAX, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], INT_MAX);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_min_value) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(INT_MIN, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], (int)2147483648);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], (int)1 << 31);
}
END_TEST

Suite *s21_from_int_to_decimal_suite(void) {
  Suite *s;
  TCase *tc_s21_from_int_to_decimal;

  s = suite_create("\033[34m \033[46m s21_from_int_to_decimal TESTS \033[0m");

  tc_s21_from_int_to_decimal = tcase_create("s21_from_int_to_decimal");

  tcase_add_test(tc_s21_from_int_to_decimal, test_s21_from_int_to_decimal_zero);
  tcase_add_test(tc_s21_from_int_to_decimal,
                 test_s21_from_int_to_decimal_positive);
  tcase_add_test(tc_s21_from_int_to_decimal,
                 test_s21_from_int_to_decimal_negative);
  tcase_add_test(tc_s21_from_int_to_decimal,
                 test_s21_from_int_to_decimal_max_int);
  tcase_add_test(tc_s21_from_int_to_decimal,
                 test_s21_from_int_to_decimal_min_int);
  tcase_add_test(tc_s21_from_int_to_decimal,
                 test_s21_from_int_to_decimal_out_of_range_high);
  tcase_add_test(tc_s21_from_int_to_decimal,
                 test_s21_from_int_to_decimal_out_of_range_low);

  tcase_add_test(tc_s21_from_int_to_decimal,
                 test_s21_from_int_to_decimal_positive_large);
  tcase_add_test(tc_s21_from_int_to_decimal,
                 test_s21_from_int_to_decimal_negative_large);
  tcase_add_test(tc_s21_from_int_to_decimal,
                 test_s21_from_int_to_decimal_max_abs);
  tcase_add_test(tc_s21_from_int_to_decimal,
                 test_s21_from_int_to_decimal_min_abs);
  tcase_add_test(tc_s21_from_int_to_decimal,
                 test_s21_from_int_to_decimal_max_value);
  tcase_add_test(tc_s21_from_int_to_decimal,
                 test_s21_from_int_to_decimal_min_value);

  suite_add_tcase(s, tc_s21_from_int_to_decimal);
  return s;
}
