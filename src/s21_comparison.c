#include "s21_decimal.h"

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  int ret = 0;
  if ((s21_get_sign(num1) == 0 && s21_get_sign(num2) == 1) ||
      (s21_is_zero(num1) == 0 && s21_is_zero(num2) == 0)) {
    ret = 0;
  } else if (s21_get_sign(num1) == 1 && s21_get_sign(num2) == 0) {
    ret = 1;
  } else if (s21_get_sign(num1) == 0 && s21_get_sign(num2) == 0) {
    s21_big_decimal big1, big2;
    s21_big_null_decimal(&big1);
    s21_big_null_decimal(&big2);
    s21_from_dec_to_big(num1, &big1);
    s21_from_dec_to_big(num2, &big2);
    s21_big_normalize(&big1, &big2);

    for (int i = 223; i >= 0; i--) {
      if (s21_big_check_bit(big1, i) < s21_big_check_bit(big2, i)) {
        ret = 1;
        break;
      } else if (s21_big_check_bit(big1, i) > s21_big_check_bit(big2, i)) {
        ret = 0;
        break;
      }
    }
  } else {
    s21_set_sign(&num1, 0);
    s21_set_sign(&num2, 0);
    ret = s21_is_less(num2, num1);
  }
  return ret;
}

// s21_is_less_or_equal(num1, num2) - возвращает 1, если num1 меньше или равно
// num2, иначе - 0.
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
  int ret = 0;
  if (s21_is_zero(num1) == 0 && s21_is_zero(num2) == 0)
    ret = 1;
  else if (s21_get_sign(num1) == 0 && s21_get_sign(num2) == 1) {
    ret = 0;
  } else if (s21_get_sign(num1) == 1 && s21_get_sign(num2) == 0) {
    ret = 1;
  } else if (s21_get_sign(num1) == 0 && s21_get_sign(num2) == 0) {
    s21_big_decimal big1, big2;
    s21_big_null_decimal(&big1);
    s21_big_null_decimal(&big2);
    s21_from_dec_to_big(num1, &big1);
    s21_from_dec_to_big(num2, &big2);
    s21_big_normalize(&big1, &big2);
    int fl = 0;
    for (int i = 223; i >= 0; i--) {
      if (s21_big_check_bit(big1, i) < s21_big_check_bit(big2, i)) {
        ret = 1;
        fl = 1;
        break;
      } else if (s21_big_check_bit(big1, i) > s21_big_check_bit(big2, i)) {
        ret = 0;
        fl = 1;
        break;
      }
    }
    if (fl == 0) ret = 1;
  } else {
    s21_set_sign(&num1, 0);
    s21_set_sign(&num2, 0);
    ret = s21_is_less_or_equal(num2, num1);
  }
  return ret;
}

// s21_is_greater(num1, num2) - возвращает 1, если num1 больше num2, иначе - 0.
int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  int ret = 0;
  if ((s21_get_sign(num1) == 1 && s21_get_sign(num2) == 0) ||
      (s21_is_zero(num1) == 0 && s21_is_zero(num2) == 0)) {
    ret = 0;
  } else if (s21_get_sign(num1) == 0 && s21_get_sign(num2) == 1) {
    ret = 1;
  } else if (s21_get_sign(num1) == 0 && s21_get_sign(num2) == 0) {
    s21_big_decimal big1, big2;
    s21_big_null_decimal(&big1);
    s21_big_null_decimal(&big2);
    s21_from_dec_to_big(num1, &big1);
    s21_from_dec_to_big(num2, &big2);
    s21_big_normalize(&big1, &big2);

    for (int i = 223; i >= 0; i--) {
      if (s21_big_check_bit(big1, i) > s21_big_check_bit(big2, i)) {
        ret = 1;
        break;
      } else if (s21_big_check_bit(big1, i) < s21_big_check_bit(big2, i)) {
        ret = 0;
        break;
      }
    }
  } else {
    s21_set_sign(&num1, 0);
    s21_set_sign(&num2, 0);
    ret = s21_is_greater(num2, num1);
  }
  return ret;
}

// s21_is_greater_or_equal(num1, num2) - возвращает 1, если num1 больше или
// равно num2, иначе - 0.
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
  int ret = 0;
  if (s21_is_zero(num1) == 0 && s21_is_zero(num2) == 0)
    ret = 1;
  else if (s21_get_sign(num1) == 0 && s21_get_sign(num2) == 1) {
    ret = 1;
  } else if (s21_get_sign(num1) == 1 && s21_get_sign(num2) == 0) {
    ret = 0;
  } else if (s21_get_sign(num1) == 0 && s21_get_sign(num2) == 0) {
    s21_big_decimal big1, big2;
    s21_big_null_decimal(&big1);
    s21_big_null_decimal(&big2);
    s21_from_dec_to_big(num1, &big1);
    s21_from_dec_to_big(num2, &big2);
    s21_big_normalize(&big1, &big2);

    int fl = 0;
    for (int i = 223; i >= 0; i--) {
      if (s21_big_check_bit(big1, i) > s21_big_check_bit(big2, i)) {
        ret = 1;
        fl = 1;
        break;
      } else if (s21_big_check_bit(big1, i) < s21_big_check_bit(big2, i)) {
        ret = 0;
        fl = 1;
        break;
      }
    }
    if (fl == 0) ret = 1;
  } else {
    s21_set_sign(&num1, 0);
    s21_set_sign(&num2, 0);
    ret = s21_is_greater_or_equal(num2, num1);
  }
  return ret;
}

// s21_is_equal(num1, num2) - возвращает 1, если num1 равно num2, иначе - 0.
int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int ret = 0;
  if (s21_is_less_or_equal(num1, num2) && s21_is_greater_or_equal(num1, num2))
    ret = 1;
  return ret;
}

//     s21_is_not_equal(num1, num2) - возвращает 1, если num1 не равно num2,
//     иначе - 0.

int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  int ret = 0;
  if (!s21_is_equal(num1, num2)) ret = 1;
  return ret;
}