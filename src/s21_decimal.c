#include "s21_decimal.h"

s21_big_decimal s21_zero_point_five = {
    {(int)5, (int)0, (int)0, (int)0, (int)0, (int)0, (int)0, (int)65536}};

bool s21_check_bit(const s21_decimal number, int bitPosition) {
  if (bitPosition < 0 || bitPosition >= 128) {
    printf("Invalid bit position\n");
    return false;
  }

  int index = bitPosition / 32;
  int bitInIndex = bitPosition % 32;

  return (number.bits[index] & (1 << bitInIndex));
}

void s21_set_bit(s21_decimal *number, int bitPosition, bool value) {
  if (bitPosition < 0 || bitPosition >= 128) {
    printf("Invalid bit position\n");
    return;
  }

  int index = bitPosition / 32;
  int bitInIndex = bitPosition % 32;

  if (value) {
    number->bits[index] |= (1 << bitInIndex);
  } else {
    number->bits[index] &= ~(1 << bitInIndex);
  }
}

int s21_is_zero(const s21_decimal number) {
  int flag = 0;
  for (int n = 0; n < 96; n++) {
    if (s21_check_bit(number, n) == 1) {
      flag = 1;
    }
  }
  return flag;
}

void s21_null_decimal(s21_decimal *number) {
  for (int n = 0; n < 128; n++) {
    s21_set_bit(number, n, false);
  }
}

int s21_get_sign(const s21_decimal number) {
  return s21_check_bit(number, 127);
}

void s21_set_sign(s21_decimal *number, int sign) {
  s21_set_bit(number, 127, sign);
}

int s21_get_scale(const s21_decimal number) {
  short int mask = 0b0000000011111111;
  short int scale = 0;
  scale = (number.bits[3] >> 16) & mask;
  return scale;
}

void s21_set_scale(s21_decimal *number, int scale) {
  number->bits[3] = (scale << 16);
}

void s21_printBinary(const s21_decimal number) {
  for (int j = 0; j < 4; j++) {
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
      int bit = (number.bits[j] >> i) & 1;
      printf("%d", bit);
    }
    printf("\n");
  }
}

int s21_is_round(s21_decimal value, s21_big_decimal copy) {
  int ret = 0;
  s21_big_decimal val;
  s21_big_null_decimal(&val);
  s21_from_dec_to_big(value, &val);
  val.bits[7] = 0, copy.bits[7] = 0;

  for (int i = 0; i < s21_get_scale(value); i++)
    s21_mult_big_decimal_by_10(&copy);

  s21_big_decimal sub;
  s21_big_null_decimal(&sub);

  s21_big_sub(val, copy, &sub);
  s21_big_set_scale(&sub, s21_get_scale(value));
  if (s21_big_is_greater(sub, s21_zero_point_five) ||
      s21_big_is_equal(sub, s21_zero_point_five))
    ret = 1;
  return ret;
}

void s21_from_float_to_decimal_parser(char buffer[50], int *exp, int *sign,
                                      int *num, int *free_zeros) {
  int e_sign = 0;
  int e_flag = 0;
  *sign = 0;
  for (int i = 0; i < 50; i++) {
    if (i == 0 && buffer[i] == '-') {
      *sign = 1;
      continue;
    }
    while (buffer[i] != 'e' && !e_flag) {
      if (buffer[i] >= 48 && buffer[i] <= 57) {
        *num = *num * 10 + (int)(buffer[i] - 48);
        if (buffer[i] == '0')
          (*free_zeros)++;
        else
          *free_zeros = 0;
      }
      i++;
    }
    if (buffer[i] == 'e') {
      e_flag++;
      i++;
      if (buffer[i] == '-') e_sign = 1;
      i++;
      *exp = *exp * 10 + (int)(buffer[i] - 48);
      i++;
      *exp = *exp * 10 + (int)(buffer[i] - 48);
      break;
    }
  }
  if (e_sign) *exp = -*exp;
}

int s21_big_get_scale(const s21_big_decimal number) {
  short int mask = 0b0111111111111111;
  short int scale = 0;
  scale = (number.bits[7] >> 16) & mask;
  return scale;
}

void s21_big_normalize(s21_big_decimal *num1, s21_big_decimal *num2) {
  s21_big_decimal num2_cpy = *num2;
  int scale1 = s21_big_get_scale(*num1), scale2 = s21_big_get_scale(*num2);
  if (scale1 > scale2) {
    int diff = scale1 - scale2;
    s21_big_decimal num2_cpy1 = *num2, num2_cpy3 = *num2;
    for (int i = 0; i < diff; i++) {
      s21_big_shift_left(&num2_cpy1, 1);
      s21_big_shift_left(&num2_cpy3, 3);
      s21_big_add(num2_cpy1, num2_cpy3, &num2_cpy);
      num2_cpy1 = num2_cpy, num2_cpy3 = num2_cpy;
    }
    *num2 = num2_cpy;
    s21_big_set_scale(num2, scale1);

  } else if (scale1 < scale2) {
    s21_big_normalize(num2, num1);
  }
}

void s21_big_add(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal *result) {
  int carry = 0;
  if (s21_big_check_bit(value_1, 255) == 0 &&
      s21_big_check_bit(value_2, 255) == 0) {
    for (int i = 0; i < 224; i++) {
      int bit_sum =
          s21_big_check_bit(value_1, i) + s21_big_check_bit(value_2, i) + carry;
      s21_big_set_bit(result, i, bit_sum & 1);
      carry = (bit_sum >> 1) & 1;
    }
  } else if (s21_big_check_bit(value_1, 255) == 1 &&
             s21_big_check_bit(value_2, 255) == 0) {
    s21_big_sub(value_2, value_1, result);
  } else if (s21_big_check_bit(value_1, 255) == 0 &&
             s21_big_check_bit(value_2, 255) == 1) {
    s21_big_sub(value_1, value_2, result);
  } else {
    s21_big_set_sign(&value_1, 0);
    s21_big_set_sign(&value_2, 0);
    s21_big_add(value_1, value_2, result);
    s21_big_set_sign(result, 1);
  }
}

int s21_big_is_less(s21_big_decimal num1, s21_big_decimal num2) {
  int ret = 0;
  if ((s21_big_check_bit(num1, 255) == 0 &&
       s21_big_check_bit(num2, 255) == 1) ||
      (s21_big_is_zero(num1) == 0 && s21_big_is_zero(num2) == 0)) {
    ret = 0;
  } else if (s21_big_check_bit(num1, 255) == 1 &&
             s21_big_check_bit(num2, 255) == 0) {
    ret = 1;
  } else if (s21_big_check_bit(num1, 255) == 0 &&
             s21_big_check_bit(num2, 255) == 0) {
    s21_big_normalize(&num1, &num2);

    for (int i = 223; i >= 0; i--) {
      if (s21_big_check_bit(num1, i) < s21_big_check_bit(num2, i)) {
        ret = 1;
        break;
      } else if (s21_big_check_bit(num1, i) > s21_big_check_bit(num2, i)) {
        ret = 0;
        break;
      }
    }
  } else {
    s21_big_set_sign(&num1, 0);
    s21_big_set_sign(&num2, 0);
    ret = s21_big_is_less(num2, num1);
  }
  return ret;
}

int s21_big_is_greater(s21_big_decimal num1, s21_big_decimal num2) {
  int ret = 0;
  if ((s21_big_check_bit(num1, 255) == 1 &&
       s21_big_check_bit(num2, 255) == 0) ||
      (s21_big_is_zero(num1) == 0 && s21_big_is_zero(num2) == 0)) {
    ret = 0;
  } else if (s21_big_check_bit(num1, 255) == 0 &&
             s21_big_check_bit(num2, 255) == 1) {
    ret = 1;
  } else if (s21_big_check_bit(num1, 255) == 0 &&
             s21_big_check_bit(num2, 255) == 0) {
    s21_big_normalize(&num1, &num2);

    for (int i = 223; i >= 0; i--) {
      if (s21_big_check_bit(num1, i) > s21_big_check_bit(num2, i)) {
        ret = 1;
        break;
      } else if (s21_big_check_bit(num1, i) < s21_big_check_bit(num2, i)) {
        ret = 0;
        break;
      }
    }
  } else {
    s21_big_set_sign(&num1, 0);
    s21_big_set_sign(&num2, 0);
    ret = s21_big_is_greater(num2, num1);
  }
  return ret;
}

void s21_big_null_decimal(s21_big_decimal *number) {
  for (int n = 0; n < 256; n++) {
    s21_big_set_bit(number, n, false);
  }
}

int s21_big_is_equal(s21_big_decimal num1, s21_big_decimal num2) {
  int ret = 1;
  for (int i = 0; i < 256; i++) {
    if (s21_big_check_bit(num1, i) != s21_big_check_bit(num2, i)) {
      ret = 0;
      break;
    }
  }
  return ret;
}

void s21_big_sub(s21_big_decimal val1, s21_big_decimal val2,
                 s21_big_decimal *result) {
  if (s21_big_check_bit(val1, 255) == 0 && s21_big_check_bit(val2, 255) == 0) {
    int carry = 0, carry_flag = 0;
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
      s21_big_set_bit(result, i, bit_sub & 1);
      carry = 0;
    }
  } else if (s21_big_check_bit(val1, 255) == 1 &&
             s21_big_check_bit(val2, 255) == 0) {
    s21_big_set_sign(&val1, 0);
    s21_big_set_sign(&val2, 0);
    s21_big_add(val1, val2, result);
    s21_big_set_sign(result, 1);
  } else if (s21_big_check_bit(val1, 255) == 0 &&
             s21_big_check_bit(val2, 255) == 1) {
    s21_big_set_sign(&val2, 0);
    s21_big_add(val1, val2, result);
  } else {
    s21_big_set_sign(&val1, 0);
    s21_big_add(val2, val1, result);
  }
}

void s21_big_shift_left(s21_big_decimal *num, int shift_value) {
  unsigned memory = 0;
  for (int i = 0; i < (int)(sizeof(s21_big_decimal) / sizeof(unsigned) - 1);
       ++i) {
    unsigned temp = num->bits[i];
    num->bits[i] <<= shift_value;
    num->bits[i] |= memory;
    memory = temp >> (32 - shift_value);
  }
}

void s21_big_shift_right(s21_big_decimal *num, int shift_value) {
  unsigned memory = 0;
  for (int i = (int)(sizeof(s21_big_decimal) / sizeof(unsigned) - 2); i >= 0;
       --i) {
    unsigned temp = num->bits[i];
    unsigned polozh_sdvig = (unsigned)num->bits[i] >> shift_value;
    num->bits[i] = polozh_sdvig;
    num->bits[i] |= memory;
    memory = temp << (32 - shift_value);
  }
}

void s21_from_dec_to_big(s21_decimal src, s21_big_decimal *dest) {
  for (int i = 0; i < 96; i++) s21_big_set_bit(dest, i, s21_check_bit(src, i));
  s21_big_set_scale(dest, s21_get_scale(src));
  s21_big_set_sign(dest, s21_get_sign(src));
}

bool s21_big_check_bit(const s21_big_decimal number, int bitPosition) {
  if (bitPosition < 0 || bitPosition >= 256) return false;
  int index = bitPosition / 32;
  int bitInIndex = bitPosition % 32;
  return (number.bits[index] & (1 << bitInIndex));
}

void s21_big_set_sign(s21_big_decimal *number, int sign) {
  s21_big_set_bit(number, 255, sign);
}

void s21_big_set_bit(s21_big_decimal *number, int bitPosition, bool value) {
  if (bitPosition < 0 || bitPosition >= 256) return;
  int index = bitPosition / 32;
  int bitInIndex = bitPosition % 32;
  if (value)
    number->bits[index] |= (1 << bitInIndex);
  else
    number->bits[index] &= ~(1 << bitInIndex);
}

void s21_big_set_scale(s21_big_decimal *number, int scale) {
  int sign = s21_big_check_bit(*number, 255);
  number->bits[7] = (scale << 16);
  s21_big_set_sign(number, sign);
}

void s21_big_printBinary(const s21_big_decimal number) {
  for (int j = 0; j < 8; j++) {
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
      int bit = (number.bits[j] >> i) & 1;
      printf("%d", bit);
    }
    printf("\n");
  }
}

void s21_mult_big_decimal_by_10(s21_big_decimal *value) {
  s21_big_decimal num1 = *value, num3 = *value;
  s21_big_shift_left(&num1, 1);
  s21_big_shift_left(&num3, 3);
  s21_big_add(num1, num3, value);
}

int s21_is_greater_than_max(s21_big_decimal num1) {
  s21_decimal MAX_DEC = {{(int)(-1), (int)(-1), (int)(-1), (int)0}};
  int ret = 0;
  if (s21_big_check_bit(num1, 255) == 1) {
    ret = 0;
  } else {
    s21_big_decimal max, num1_cpy;
    num1_cpy = num1;
    s21_big_null_decimal(&max);
    s21_from_dec_to_big(MAX_DEC, &max);
    s21_big_normalize(&max, &num1_cpy);
    for (int i = 223; i >= 0; i--) {
      if (s21_big_check_bit(num1_cpy, i) > s21_big_check_bit(max, i)) {
        ret = 1;
        break;
      } else if (s21_big_check_bit(num1_cpy, i) < s21_big_check_bit(max, i)) {
        ret = 0;
        break;
      }
    }
  }
  return ret;
}

int to_small_for_mul_div(s21_big_decimal num) {
  return !check_three_first_ints_in_big_decimal(num) &&
         (s21_big_get_scale(num) > 28);
}

int s21_big_is_zero(const s21_big_decimal number) {
  int flag = 0;
  for (int n = 0; n < 224; n++) {
    if (s21_big_check_bit(number, n) == 1) {
      flag = 1;
    }
  }
  return flag;
}

int s21_is_less_than_min(s21_big_decimal num1) {
  int ret = 0;
  s21_big_set_sign(&num1, 0);
  s21_decimal MIN_DEC = {{(int)1, (int)0, (int)0, (int)1835008}};
  if ((s21_big_is_zero(num1) == 0)) {
    ret = 0;
  } else {
    s21_big_decimal min, num1_cpy;
    num1_cpy = num1;
    s21_big_null_decimal(&min);
    s21_from_dec_to_big(MIN_DEC, &min);
    s21_big_normalize(&min, &num1_cpy);

    for (int i = 223; i >= 0; i--) {
      if (s21_big_check_bit(num1_cpy, i) < s21_big_check_bit(min, i)) {
        ret = 1;
        break;
      } else if (s21_big_check_bit(num1_cpy, i) > s21_big_check_bit(min, i)) {
        ret = 0;
        break;
      }
    }
  }
  return ret;
}

s21_decimal s21_from_big_to_dec(s21_big_decimal dec) {
  s21_decimal result;
  s21_null_decimal(&result);
  int exp = s21_big_get_scale(dec);
  while (check_three_first_ints_in_big_decimal(dec)) {
    bank_round(&dec);
    if (exp) {
      exp--;
      s21_big_set_scale(&dec, exp);
    }
  }

  result.bits[0] = dec.bits[0];
  result.bits[1] = dec.bits[1];
  result.bits[2] = dec.bits[2];
  result.bits[3] = dec.bits[7];
  return result;
}

int check_three_first_ints_in_big_decimal(s21_big_decimal dec) {
  int result = 0;
  for (int i = 96; i < 224; i++) {
    if (s21_big_check_bit(dec, i)) {
      result = 1;
      break;
    }
  }
  return result;
}

void bank_round(s21_big_decimal *dec) {
  int last_number = 0;

  if (s21_big_check_bit(*dec, 0)) {
    last_number += 1;
  }

  for (int i = 1; i < 224; i++) {
    if (s21_big_check_bit(*dec, i)) {
      if (i % 4 == 0) {
        last_number += 6;
      } else if (i % 4 == 1) {
        last_number += 2;
      } else if (i % 4 == 2) {
        last_number += 4;
      } else {
        last_number += 8;
      }
    }
  }

  last_number %= 10;
  s21_div_big_decimal_by_10(*dec, dec);

  if (last_number >= 5) {
    s21_big_decimal buf = {{1, 0, 0, 0, 0, 0, 0, 0}};
    s21_big_set_scale(&buf, s21_big_get_scale(*dec));

    s21_big_set_bit(&buf, s21_big_check_bit(*dec, 255), 255);
    s21_big_add(*dec, buf, dec);
  }

  if (last_number == 5) {
    if (s21_big_check_bit(*dec, 0)) {
      s21_big_set_bit(dec, 0, 0);
    }
  }
}

int s21_div_big_decimal_by_10(s21_big_decimal dec, s21_big_decimal *result) {
  int bit = 0;
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_set_scale(&ten, s21_big_get_scale(dec));
  s21_big_set_bit(&dec, 255, 0);
  s21_big_null_decimal(result);

  int first_significant_bit = 223;
  for (; first_significant_bit >= 0; first_significant_bit--) {
    if (s21_big_check_bit(dec, first_significant_bit)) {
      break;
    }
  }
  int sdvig = 0;

  while (bit == 0 && sdvig < 193) {
    sdvig++;
    s21_big_shift_left(&ten, 1);
    bit = dec.bits[5] & (1 << 31);
    if (s21_big_check_bit(ten, first_significant_bit)) {
      break;
    }
  }
  sdvig += 1;
  while (sdvig-- && sdvig != 192) {
    s21_big_shift_left(result, 1);

    if (s21_big_is_greater(ten, dec)) {
      s21_big_set_bit(result, 0, 0);
    } else {
      s21_big_sub(dec, ten, &dec);
      s21_big_set_bit(result, 0, 1);
    }
    s21_big_shift_right(&ten, 1);
  }
  s21_big_set_scale(result, s21_big_get_scale(dec));

  return bit;
}