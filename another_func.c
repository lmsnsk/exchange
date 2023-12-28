#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = check_decimal(value);
  if (!error) {
    null_decimal(result);
    invert_sign(&value);
    for (int i = 0; i < 4; i++) result->bits[i] = value.bits[i];
  }
  return error;  /////////////////////////??
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = check_decimal(value);
  if (!error) {
    int scale = get_scale(value);
    if (!scale) {
      *result = value;
    } else {
      int flag = 0;
      int sign = get_sign(value);
      null_decimal(result);

      for (int i = 0; i < scale; i++) {
        if (get_bit(value, i)) {
          flag = 1;
          break;
        }
      }

      for (int i = 0; i < scale; i++) {
        if (get_bit(value, i)) flag = 1;
      }
      if (flag && sign) result->bits[0] -= 1;
    }
  }
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = check_decimal(value);
  if (!error) {
    *result = value;
    unsigned scale = get_scale(value);

    if (scale) {
      s21_decimal ten_decimal;
      unsigned sign = get_sign(value);
      s21_from_int_to_decimal(10, &ten_decimal);
      big_dec big_ten_decimal = from_decimal_to_big_decimal(ten_decimal);
      big_dec big_result = from_decimal_to_big_decimal(value);

      while (scale > 0) {
        big_dec remainder = big_result;
        big_div_ten(&big_result, &remainder, big_ten_decimal);
        scale--;
      }
      from_big_decimal_to_decimal(big_result, result);
      if (sign) invert_sign(result);
    }
  }
  return error;
}