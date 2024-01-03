#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = check_decimal(value);
  if (!error) {
    *result = value;
    invert_sign(result);
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

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = check_decimal(value);
  if (!error) {
    int scale = get_scale(value);

    if (!scale) {
      *result = value;
    } else {
      int sign = get_sign(value);
      error = s21_truncate(value, result);

      if (sign && !is_decimal_zero(value)) {
        s21_decimal minus_one;
        s21_from_int_to_decimal(-1, &minus_one);
        error = s21_add(*result, minus_one, result);
        if (error) error = 1;
      }
    }
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = check_decimal(value);
  if (!error) {
    int scale = get_scale(value);

    if (!scale) {
      *result = value;
    } else {
      unsigned sign = get_sign(value);

      big_dec big_ten_dec = from_int_to_big_decimal(10);
      big_dec big_scale_ten_dec = big_ten_dec;

      for (int i = 0; i < scale - 1; i++) {
        big_scale_ten_dec = big_mul(big_scale_ten_dec, big_ten_dec);
      }

      big_dec big_result = from_decimal_to_big_decimal(value);
      if (sign) big_invert_sign(&big_result);

      big_dec one;
      big_dec remainder = big_result;
      big_null_decimal(&one);
      one.bits[0] = 1;

      big_div_ten(&big_result, &remainder, big_scale_ten_dec);
      s21_decimal rem_small, half;
      null_decimal(&half);
      half.bits[0] = 5;
      set_scale(&half, 1);
      from_big_decimal_to_decimal(remainder, &rem_small);

      if (s21_is_greater_or_equal(rem_small, half)) {
        big_summ(big_result, one, &big_result);
      }
      from_big_decimal_to_decimal(big_result, result);
      if (sign) invert_sign(result);
    }
  }
  return error;
}