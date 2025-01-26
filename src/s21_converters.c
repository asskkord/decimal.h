#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int ret = 0;
  if (dst != NULL) {
    s21_null_decimal(dst);
    if (src == -2147483648) {
      s21_set_sign(dst, 1);
      dst->bits[0] = 0b10000000000000000000000000000000;
    } else {
      if (src < 0) {
        s21_set_sign(dst, 1);
        src = -src;
      }
      for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
        s21_set_bit(dst, i, src >> i & 1);
      }
    }
  } else
    ret = 1;
  return ret;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int ret = 0;
  int sign = s21_get_sign(src);
  int scale = s21_get_scale(src);
  if (scale <= 28 && scale >= 0 && dst != NULL) {
    s21_big_decimal num;
    s21_big_null_decimal(&num);
    s21_from_dec_to_big(src, &num);
    for (int i = 0; i < scale; i++) s21_div_big_decimal_by_10(num, &num);
    // for (int i = 0; i < scale; i++) s21_mult_big_decimal_by_10(&num);
    src.bits[0] = num.bits[0], src.bits[1] = num.bits[1],
    src.bits[2] = num.bits[2];
    if (src.bits[1] == 0 && src.bits[2] == 0) {
      *dst = src.bits[0];
      if (sign) *dst = -*dst;
    } else {
      ret = 1;
    }
  } else
    ret = 1;
  return ret;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int ret = 0;
  if (dst != NULL) {
    int sign = s21_check_bit(src, 127);
    *dst = ((unsigned)src.bits[2] * pow(2, 64) +
            (unsigned)src.bits[1] * pow(2, 32) + (unsigned)src.bits[0]) /
           pow(10, s21_get_scale(src));
    if (sign) {
      *dst *= -1;
    }
    if ((fabs(*dst) < 1e-28) && (fabs(*dst) > 0)) {
      ret = 1;
    }
  } else
    ret = 1;
  return ret;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_null_decimal(dst);
  int ret = 0;
  if (fabs(src) < 1e-28 && fabs(src) > 0) {
    s21_null_decimal(dst);
    ret = 1;
  } else if (fabs(src) > pow(2, 96) || isnan(src) || dst == NULL) {
    ret = 1;
  } else {
    char buffer[50];
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%e", src);
    int exp = 0, sign = 0, num = 0, free_zeros = 0;
    s21_from_float_to_decimal_parser(buffer, &exp, &sign, &num, &free_zeros);
    int true_scale = 6 - exp;
    s21_big_decimal copy;
    s21_big_null_decimal(&copy);
    copy.bits[0] = num;

    if (exp > 6) {
      for (int i = exp; exp > 6; exp--) {
        s21_mult_big_decimal_by_10(&copy);
        i++;
      }
    }

    while (true_scale > 0) {
      if (num % 10 != 0) break;
      s21_div_big_decimal_by_10(copy, &copy);
      true_scale--;
      num /= 10;
    }

    if (true_scale < 0) true_scale = 0;
    dst->bits[0] = copy.bits[0], dst->bits[1] = copy.bits[1],
    dst->bits[2] = copy.bits[2];
    s21_set_scale(dst, true_scale);
    s21_set_sign(dst, sign);
  }
  return ret;
}