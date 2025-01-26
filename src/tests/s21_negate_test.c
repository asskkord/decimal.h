#include <check.h>

#include "s21_main_tests.h"

// Function to check if two s21_decimal values are equal
int s21_decimal_equal(const s21_decimal *a, const s21_decimal *b) {
  return (a->bits[0] == b->bits[0]) && (a->bits[1] == b->bits[1]) &&
         (a->bits[2] == b->bits[2]) && (a->bits[3] == b->bits[3]);
}

// Test Case 1: Negate positive number
START_TEST(test_negate_positive) {
  s21_decimal src;
  src.bits[0] = 0x00000000;
  src.bits[1] = 0x00000000;
  src.bits[2] = 0x00000000;
  src.bits[3] = 0x0000000F;  // 15

  s21_decimal expected;
  expected.bits[0] = 0x00000000;
  expected.bits[1] = 0x00000000;
  expected.bits[2] = 0x00000000;
  expected.bits[3] = 0x8000000F;  // -15

  s21_decimal result;
  s21_negate(src, &result);

  ck_assert(s21_decimal_equal(&result, &expected));
}
END_TEST

START_TEST(test_negate_negative) {
  s21_decimal src;
  src.bits[0] = 0x00000000;
  src.bits[1] = 0x00000000;
  src.bits[2] = 0x00000000;
  src.bits[3] = 0x8000000F;  // -15

  s21_decimal expected;
  expected.bits[0] = 0x00000000;
  expected.bits[1] = 0x00000000;
  expected.bits[2] = 0x00000000;
  expected.bits[3] = 0x0000000F;  // 15

  s21_decimal result;
  s21_negate(src, &result);

  ck_assert(s21_decimal_equal(&result, &expected));
}
END_TEST

// Test Case 3: Negate zero
START_TEST(test_negate_zero) {
  s21_decimal src;
  src.bits[0] = 0x00000000;
  src.bits[1] = 0x00000000;
  src.bits[2] = 0x00000000;
  src.bits[3] = 0x00000000;  // 0

  s21_decimal expected;
  expected.bits[0] = 0x00000000;
  expected.bits[1] = 0x00000000;
  expected.bits[2] = 0x00000000;
  expected.bits[3] = 0x80000000;  // 0

  s21_decimal result;
  s21_negate(src, &result);

  ck_assert(s21_decimal_equal(&result, &expected));
}
END_TEST

// Test Case 4: Negate minimum negative value
START_TEST(test_negate_min_negative) {
  s21_decimal src;
  src.bits[0] = 0x80000000;  // Minimum negative value
  src.bits[1] = 0x00000000;
  src.bits[2] = 0x00000000;
  src.bits[3] = 0x00000000;

  s21_decimal expected;
  expected.bits[0] = 0x80000000;  // No change
  expected.bits[1] = 0x00000000;
  expected.bits[2] = 0x00000000;
  expected.bits[3] = 0x80000000;  // Only change the sign bit

  s21_decimal result;
  s21_negate(src, &result);

  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3],
                   expected.bits[3]);  // Check only the sign bit
}
END_TEST

// Test Case 5: Negate maximum positive value
START_TEST(test_negate_max_positive) {
  s21_decimal src;
  src.bits[0] = 0x7FFFFFFF;  // Maximum positive value
  src.bits[1] = 0xFFFFFFFF;
  src.bits[2] = 0xFFFFFFFF;
  src.bits[3] = 0xFFFFFFFF;

  s21_decimal expected;
  expected.bits[0] = 0x7FFFFFFF;  // No change
  expected.bits[1] = 0xFFFFFFFF;
  expected.bits[2] = 0xFFFFFFFF;
  expected.bits[3] = 0x7FFFFFFF;  // Only change the sign bit

  s21_decimal result;
  s21_negate(src, &result);

  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3],
                   expected.bits[3]);  // Check only the sign bit
}
END_TEST

// Test Case 6: Negate with NULL result pointer
START_TEST(test_negate_null_result) {
  s21_decimal src;
  src.bits[0] = 0x12345678;
  src.bits[1] = 0x87654321;
  src.bits[2] = 0xABCDEF01;
  src.bits[3] = 0x80000000;  // Minimum negative value

  s21_decimal *result = NULL;

  int flag = s21_negate(src, result);

  ck_assert_int_eq(
      flag, 1);  // Check that flag is set to 1, indicating NULL result pointer
}
END_TEST

// Function to create test suite
Suite *s21_negate_suite(void) {
  Suite *suite;
  TCase *tc_core;

  suite = suite_create("\033[34m \033[46m s21_negate TESTS \033[0m");

  // Core test case
  tc_core = tcase_create("Core");

  // Add individual tests to the test case
  tcase_add_test(tc_core, test_negate_positive);
  tcase_add_test(tc_core, test_negate_negative);
  tcase_add_test(tc_core, test_negate_zero);
  tcase_add_test(tc_core, test_negate_min_negative);
  tcase_add_test(tc_core, test_negate_max_positive);
  tcase_add_test(tc_core, test_negate_null_result);

  // Add the test case to the suite
  suite_add_tcase(suite, tc_core);

  return suite;
}