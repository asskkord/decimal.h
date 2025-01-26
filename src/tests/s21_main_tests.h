#ifndef S21_MAIN_TESTS_H
#define S21_MAIN_TESTS_H

#define EXPONENT_MINUS_28 2149318656  // 0b10000000000111000000000000000000
#define EXPONENT_PLUS_28 1835008      // 0b00000000000111000000000000000000
#define MINUS 2147483648              // 0b10000000000000000000000000000000
#define EXPONENT_PLUS_1 65536         // 0b00000000000000010000000000000000
#define S21_MAX_UINT 4294967295
#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

#include "../s21_decimal.h"

Suite *s21_add_suite(void);
Suite *s21_mul_suite(void);
Suite *s21_sub_suite(void);
Suite *s21_is_less_suite(void);
Suite *s21_is_equal_suite(void);
Suite *s21_is_less_or_equal_suite(void);
Suite *s21_is_greater_or_equal_suite(void);
Suite *s21_is_not_equal_suite(void);
Suite *s21_is_greater_suite(void);
Suite *s21_from_int_to_decimal_suite(void);
Suite *suite_from_float_to_decimal(void);
Suite *s21_truncate_suite(void);
Suite *s21_floor_suite(void);
Suite *s21_negate_suite(void);
Suite *suite_from_decimal_to_float(void);

Suite *suite_from_decimal_to_int(void);
Suite *s21_round_suite(void);
Suite *s21_random_suite(void);

#endif