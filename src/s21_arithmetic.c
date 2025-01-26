#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0;
  s21_null_decimal(result);
  int carry = 0, carry_flag = 0;
  if (s21_get_sign(value_1) == 0 && s21_get_sign(value_2) == 0) {
    if (s21_is_greater(value_1, value_2)) {
      s21_big_decimal val1, val2, res;
      s21_big_null_decimal(&val1);
      s21_big_null_decimal(&val2);
      s21_big_null_decimal(&res);
      s21_from_dec_to_big(value_1, &val1);
      s21_from_dec_to_big(value_2, &val2);
      s21_big_normalize(&val1, &val2);
      s21_big_set_scale(&res, s21_big_get_scale(val1));
      for (int i = 0; i < 224; i++) {
        if (s21_big_check_bit(val1, i) - s21_big_check_bit(val2, i) + carry -
                carry_flag <
            0)
          carry = 2;
        int bit_sub = s21_big_check_bit(val1, i) - s21_big_check_bit(val2, i) +
                      carry - carry_flag;
        if (carry == 2)
          carry_flag = 1;
        else
          carry_flag = 0;
        s21_big_set_bit(&res, i, bit_sub & 1);
        carry = 0;
      }
      s21_big_decimal res_plus = res;
      s21_big_set_sign(&res_plus, 0);
      if (s21_is_greater_than_max(res) && s21_big_check_bit(res, 255) == 0)
        ret = 1;
      else if (s21_big_check_bit(res, 255) == 1 &&
               s21_is_greater_than_max(res_plus))
        ret = 2;
      if (ret == 0) *result = s21_from_big_to_dec(res);
    } else if (s21_is_less(value_1, value_2)) {
      s21_sub(value_2, value_1, result);
      s21_set_sign(result, 1);
    } else {
      s21_null_decimal(result);
    }
  } else if ((s21_get_sign(value_1) == 1 && s21_get_sign(value_2) == 0)) {
    s21_set_sign(&value_1, 0);
    ret = s21_add(value_1, value_2, result);
    s21_set_sign(result, 1);
    if (ret == 1)
      ret = 2;
    else if (ret == 2)
      ret = 1;
  } else if ((s21_get_sign(value_1) == 0 && s21_get_sign(value_2) == 1)) {
    s21_set_sign(&value_2, 0);
    ret = s21_add(value_1, value_2, result);
  } else {
    s21_set_sign(&value_1, 0);
    s21_set_sign(&value_2, 0);
    ret = s21_sub(value_2, value_1, result);
  }
  return ret;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0;
  s21_null_decimal(result);
  int carry = 0;
  if (s21_get_sign(value_1) == 0 && s21_get_sign(value_2) == 0) {
    s21_big_decimal val1, val2, res;
    s21_big_null_decimal(&val1);
    s21_big_null_decimal(&val2);
    s21_big_null_decimal(&res);
    s21_from_dec_to_big(value_1, &val1);
    s21_from_dec_to_big(value_2, &val2);
    s21_big_normalize(&val1, &val2);
    s21_big_set_scale(&res, s21_big_get_scale(val1));
    for (int i = 0; i < 224; i++) {
      int bit_sum =
          s21_big_check_bit(val1, i) + s21_big_check_bit(val2, i) + carry;
      s21_big_set_bit(&res, i, bit_sum & 1);
      carry = (bit_sum >> 1) & 1;
    }
    s21_big_decimal res_plus = res;
    s21_big_set_sign(&res_plus, 0);
    if (s21_is_greater_than_max(res) && s21_big_check_bit(res, 255) == 0)
      ret = 1;
    else if (s21_big_check_bit(res, 255) == 1 &&
             s21_is_greater_than_max(res_plus))
      ret = 2;
    if (ret == 0) *result = s21_from_big_to_dec(res);
  } else if ((s21_get_sign(value_1) == 1 && s21_get_sign(value_2) == 0)) {
    s21_set_sign(&value_1, 0);
    ret = s21_sub(value_2, value_1, result);
  } else if ((s21_get_sign(value_1) == 0 && s21_get_sign(value_2) == 1)) {
    s21_set_sign(&value_2, 0);
    ret = s21_sub(value_1, value_2, result);
  } else {
    s21_set_sign(&value_1, 0);
    s21_set_sign(&value_2, 0);
    ret = s21_add(value_2, value_1, result);
    s21_set_sign(result, 1);
    if (ret == 1)
      ret = 2;
    else if (ret == 2)
      ret = 1;
  }
  return ret;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0;
  if (s21_is_zero(value_1) == 0 || s21_is_zero(value_2) == 0)
    s21_null_decimal(result);
  else {
    s21_null_decimal(result);
    s21_big_decimal val1, val2, res;
    s21_big_null_decimal(&val1);
    s21_big_null_decimal(&val2);
    s21_big_null_decimal(&res);
    s21_from_dec_to_big(value_1, &val1);
    s21_from_dec_to_big(value_2, &val2);

    s21_big_set_sign(
        &res,
        (s21_big_check_bit(val1, 255) + s21_big_check_bit(val2, 255)) % 2);
    s21_big_set_scale(&res, s21_big_get_scale(val1) + s21_big_get_scale(val2));
    for (int i = 0; i < 224; i++) {
      bool is_mul = s21_big_check_bit(val2, i);
      if (is_mul) {
        s21_big_add(res, val1, &res);
      }
      s21_big_shift_left(&val1, 1);
    }
    s21_big_decimal res_plus = res;
    s21_big_set_sign(&res_plus, 0);
    if (s21_is_greater_than_max(res) && s21_big_check_bit(res, 255) == 0 &&
        !to_small_for_mul_div(res))
      ret = 1;
    else if (to_small_for_mul_div(res) ||
             (s21_big_check_bit(res, 255) == 1 &&
              s21_is_greater_than_max(res_plus)) ||
             s21_is_less_than_min(res_plus))
      ret = 2;
    if (ret == 0) *result = s21_from_big_to_dec(res);
  }
  return ret;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0;
  if (s21_is_zero(value_2) == 0)
    ret = 3;
  else if (s21_is_zero(value_1) == 0)
    s21_null_decimal(result);
  else {
    s21_null_decimal(result);
    s21_big_decimal val1, val2, res;
    s21_big_null_decimal(&val1);
    s21_big_null_decimal(&val2);
    s21_big_null_decimal(&res);
    s21_from_dec_to_big(value_1, &val1);
    s21_from_dec_to_big(value_2, &val2);

    int sign =
        (s21_big_check_bit(val1, 255) + s21_big_check_bit(val2, 255)) % 2;
    int scale = s21_big_get_scale(val1) - s21_big_get_scale(val2);

    s21_big_decimal real_part = val2;
    s21_big_decimal reminder = val1;
    s21_big_set_scale(&real_part, 0);
    s21_big_set_sign(&real_part, 0);
    s21_big_set_scale(&reminder, 0);
    s21_big_set_sign(&reminder, 0);
    while (1) {
      s21_big_decimal rezz;
      s21_big_null_decimal(&rezz);
      while (s21_big_is_less(real_part, reminder) ||
             s21_big_is_equal(real_part, reminder)) {
        s21_big_decimal res_part = {{1, 0, 0, 0, 0, 0, 0, 0}};
        while (s21_big_is_less(real_part, reminder) ||
               s21_big_is_equal(real_part, reminder)) {
          s21_big_shift_left(&real_part, 1);
          s21_big_shift_left(&res_part, 1);
        }
        s21_big_shift_right(&real_part, 1);
        s21_big_shift_right(&res_part, 1);
        s21_big_sub(reminder, real_part, &reminder);
        s21_big_add(rezz, res_part, &rezz);
        real_part = val2;
      }
      s21_mult_big_decimal_by_10(&res);
      s21_big_add(res, rezz, &res);

      if (!s21_big_is_zero(reminder)) break;

      s21_mult_big_decimal_by_10(&reminder);
      scale++;
      if (scale == 28 || check_three_first_ints_in_big_decimal(res)) break;
    }

    s21_big_set_scale(&res, scale);
    s21_big_set_sign(&res, sign);

    s21_big_decimal res_plus = res;
    s21_big_set_sign(&res_plus, 0);
    if ((s21_is_greater_than_max(res) && s21_big_check_bit(res, 255) == 0 &&
         !to_small_for_mul_div(res)) ||
        scale < 0)
      ret = 1;
    else if (to_small_for_mul_div(res) ||
             (s21_big_check_bit(res, 255) == 1 &&
              s21_is_greater_than_max(res_plus)) ||
             s21_is_less_than_min(res_plus))
      ret = 2;
    if (ret == 0) *result = s21_from_big_to_dec(res);
  }
  return ret;
}