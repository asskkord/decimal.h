#include "s21_decimal.h"

s21_big_decimal s21_one = {
    {(int)1, (int)0, (int)0, (int)0, (int)0, (int)0, (int)0, (int)0}};

int s21_negate(s21_decimal value, s21_decimal *result) {
  int ret = 0;
  if (result == NULL)
    ret = 1;
  else {
    s21_null_decimal(result);
    s21_set_sign(&value, (s21_get_sign(value) + 1) % 2);
    *result = value;
  }
  return ret;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int ret = 0;
  if (result == NULL || s21_get_scale(value) > 28)
    ret = 1;
  else {
    if (s21_get_scale(value) == 0)
      *result = value;
    else {
      s21_big_decimal copy;
      s21_null_decimal(result);
      s21_big_null_decimal(&copy);
      s21_from_dec_to_big(value, &copy);
      for (int i = 0; i < s21_get_scale(value); i++)
        s21_div_big_decimal_by_10(copy, &copy);
      if (s21_get_sign(value)) s21_big_add(copy, s21_one, &copy);
      result->bits[0] = copy.bits[0], result->bits[1] = copy.bits[1],
      result->bits[2] = copy.bits[2];
      s21_set_sign(result, s21_get_sign(value));
    }
  }
  return ret;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int ret = 0;
  if (result == NULL || s21_get_scale(value) > 28)
    ret = 1;
  else {
    if (s21_get_scale(value) == 0)
      *result = value;
    else {
      s21_big_decimal copy;
      s21_null_decimal(result);
      s21_big_null_decimal(&copy);
      s21_from_dec_to_big(value, &copy);
      for (int i = 0; i < s21_get_scale(value); i++)
        s21_div_big_decimal_by_10(copy, &copy);
      if (s21_is_round(value, copy)) s21_big_add(copy, s21_one, &copy);
      result->bits[0] = copy.bits[0], result->bits[1] = copy.bits[1],
      result->bits[2] = copy.bits[2];
      s21_set_sign(result, s21_get_sign(value));
    }
  }
  return ret;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int ret = 0;
  if (result == NULL || s21_get_scale(value) > 28)
    ret = 1;
  else {
    if (s21_get_scale(value) == 0)
      *result = value;
    else {
      s21_big_decimal copy;
      s21_null_decimal(result);
      s21_big_null_decimal(&copy);
      s21_from_dec_to_big(value, &copy);
      for (int i = 0; i < s21_get_scale(value); i++)
        s21_div_big_decimal_by_10(copy, &copy);
      result->bits[0] = copy.bits[0], result->bits[1] = copy.bits[1],
      result->bits[2] = copy.bits[2];
      s21_set_sign(result, s21_get_sign(value));
    }
  }
  return ret;
}