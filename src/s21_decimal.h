#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  int bits[8];
} s21_big_decimal;

int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_is_round(s21_decimal value, s21_big_decimal copy);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
s21_decimal s21_from_big_to_dec(s21_big_decimal dec);
int check_three_first_ints_in_big_decimal(s21_big_decimal dec);
void bank_round(s21_big_decimal *dec);
void s21_big_shift_right(s21_big_decimal *num, int shift_value);
int s21_big_is_greater(s21_big_decimal num1, s21_big_decimal num2);
void s21_big_sub(s21_big_decimal val1, s21_big_decimal val2,
                 s21_big_decimal *result);
void s21_mult_big_decimal_by_10(s21_big_decimal *value);
int s21_is_less_than_min(s21_big_decimal num1);
int s21_is_greater_than_max(s21_big_decimal num1);
int s21_div_big_decimal_by_10(s21_big_decimal dec, s21_big_decimal *result);
int s21_big_is_zero(const s21_big_decimal number);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_big_null_decimal(s21_big_decimal *number);
void s21_big_printBinary(const s21_big_decimal number);
void s21_big_set_scale(s21_big_decimal *number, int scale);
void s21_big_set_bit(s21_big_decimal *number, int bitPosition, bool value);
void s21_big_set_sign(s21_big_decimal *number, int sign);
bool s21_big_check_bit(const s21_big_decimal number, int bitPosition);
void s21_from_dec_to_big(s21_decimal src, s21_big_decimal *dest);
void s21_shift_left(s21_big_decimal *num, int shift_value);
void s21_big_normalize(s21_big_decimal *num1, s21_big_decimal *num2);
void s21_big_add(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal *result);
void s21_big_shift_left(s21_big_decimal *num, int shift_value);
int s21_big_get_scale(const s21_big_decimal number);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);
int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater(s21_decimal num1, s21_decimal num2);
int s21_is_less(s21_decimal num1, s21_decimal num2);
bool s21_check_bit(const s21_decimal number, int bitPosition);
void s21_set_bit(s21_decimal *number, int bitPosition, bool value);
int s21_is_zero(const s21_decimal number);
void s21_null_decimal(s21_decimal *number);
int s21_get_sign(const s21_decimal number);
void s21_set_sign(s21_decimal *number, int sign);
int s21_get_scale(const s21_decimal number);
void s21_set_scale(s21_decimal *number, int scale);
void s21_printBinary(const s21_decimal number);
int s21_big_is_less(s21_big_decimal num1, s21_big_decimal num2);
int s21_big_is_equal(s21_big_decimal num1, s21_big_decimal num2);
int to_small_for_mul_div(s21_big_decimal num);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
void s21_from_float_to_decimal_parser(char buffer[50], int *exp, int *sign,
                                      int *num, int *free_zeros);

#endif
