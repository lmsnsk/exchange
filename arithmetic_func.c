#include "s21_decimal.h"

int add_and_sub_core(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result, int is_sub) {
  int error = 0;
  big_dec big_result;
  big_null_decimal(&big_result);
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  int scale_1 = get_scale(value_1);
  int scale_2 = get_scale(value_2);
  big_dec big_val_1 = from_decimal_to_big_decimal(value_1);
  big_dec big_val_2 = from_decimal_to_big_decimal(value_2);

  if (scale_1 > scale_2)
    big_normalization(&big_val_2, scale_1 - scale_2);
  else if (scale_1 != scale_2)
    big_normalization(&big_val_1, scale_2 - scale_1);

  if (abs(sign_1 - sign_2) == is_sub) {
    big_summ(big_val_1, big_val_2, &big_result);
    if (sign_1) big_invert_sign(&big_result);
  } else {
    invert_sign(&value_1);
    if (s21_is_equal(value_1, value_1)) {
      big_null_decimal(&big_result);
    } else {
      if (sign_1 && is_sub) invert_sign(&value_2);

      if (s21_is_greater(value_1, value_2)) {
        big_diff(big_val_1, big_val_2, &big_result);
        if (sign_1) big_invert_sign(&big_result);
      } else {
        big_diff(big_val_2, big_val_1, &big_result);
        if (sign_2) big_invert_sign(&big_result);
      }
    }
  }
  big_set_scale(&big_result, scale_1 > scale_2 ? scale_1 : scale_2);
  error = from_big_decimal_to_decimal(big_result, result);
  return error;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int is_sub = 0;
  int error = add_and_sub_core(value_1, value_2, result, is_sub);
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int is_sub = 1;
  int error = add_and_sub_core(value_1, value_2, result, is_sub);
  return error;
}

big_dec big_mul(big_dec big_val_1, big_dec big_val_2) {
  big_dec tmp_res;
  big_dec result;
  big_null_decimal(&result);

  for (int i = 0; i < (BIG_SIZE - 1) * 32; i++) {
    big_dec buffer = result;
    for (int j = 0; j < (BIG_SIZE - 1) * 32; j++) {
      int res_bit = big_get_bit(big_val_1, i) * big_get_bit(big_val_2, j);
      big_set_bit(&tmp_res, j, res_bit);
    }
    big_shift_left(&tmp_res, i);
    big_summ(buffer, tmp_res, &result);
  }
  return result;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  big_dec big_result;
  big_null_decimal(&big_result);
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  int scale_1 = get_scale(value_1);
  int scale_2 = get_scale(value_2);
  big_dec big_val_1 = from_decimal_to_big_decimal(value_1);
  big_dec big_val_2 = from_decimal_to_big_decimal(value_2);

  big_result = big_mul(big_val_1, big_val_2);
  big_set_scale(&big_result, scale_1 + scale_2);

  if (sign_1 != sign_2) big_invert_sign(&big_result);
  error = from_big_decimal_to_decimal(big_result, result);
  return error;
}

void big_div(big_dec *big_val_1, big_dec *big_val_2, big_dec *big_result,
             big_dec ten_big_decimal) {
  big_dec remainder = *big_val_1;
  for (int i = 0; !big_is_decimal_zero(remainder); i++) {
    for (int l = 0; l < i; l++) {
      remainder = big_mul(remainder, ten_big_decimal);
    }
    big_dec temp;
    big_dec temp_1 = *big_val_2;
    int count = 0, j = 0;
    do {
      count++;
      temp = temp_1;
      big_shift_left(&temp_1, 1);
    } while (big_is_greater(*big_val_1, temp_1));

    while (count--) {
      temp = *big_val_2;
      for (int k = 0; k < count; k++) big_shift_left(&temp, 1);

      if (big_is_greater(temp, remainder)) {
        big_shift_left(big_result, 1);
      } else {
        big_diff(*big_val_1, temp, &remainder);
        big_set_bit(big_result, j, ONE);
      }
      j++;
    }
  }
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  null_decimal(result);
  if (is_decimal_zero(value_2)) error = 3;

  if (error || is_decimal_zero(value_1)) {
    big_dec big_result;
    s21_decimal ten_decimal;
    big_null_decimal(&big_result);
    int sign_1 = get_sign(value_1);
    int sign_2 = get_sign(value_2);
    int scale_1 = get_scale(value_1);
    int scale_2 = get_scale(value_2);
    value_1.bits[3] = value_2.bits[3] = 0;

    big_dec big_val_1 = from_decimal_to_big_decimal(value_1);
    big_dec big_val_2 = from_decimal_to_big_decimal(value_2);

    s21_from_int_to_decimal(10, &ten_decimal);
    big_dec ten_big_decimal = from_decimal_to_big_decimal(ten_decimal);

    while (s21_is_less(value_1, value_2)) {
      big_val_1 = big_mul(big_val_1, ten_big_decimal);
      scale_1++;
    }

    if (s21_is_not_equal(value_1, value_2)) {
      big_div(&big_val_1, &big_val_2, &big_result, ten_big_decimal);
    } else {
      big_result.bits[0] = 1;
    }
    if (sign_1 != sign_2) big_invert_sign(&big_result);
    int res_scale = scale_1 - scale_2;
    while (res_scale < 0) {
      big_result = big_mul(big_result, ten_big_decimal);
      res_scale++;
    }
    error = from_big_decimal_to_decimal(big_result, result);
  }
  return error;
}