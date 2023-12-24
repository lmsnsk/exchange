#include "s21_decimal.h"

int add_and_sub_core(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result, int is_sub) {
  int error = 0;
  big_dec big_result;
  big_decimal_zero(&big_result);
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
      big_decimal_zero(&big_result);
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

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  big_dec big_result;
  big_decimal_zero(&big_result);
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  int scale_1 = get_scale(value_1);
  int scale_2 = get_scale(value_2);
  big_dec big_val_1 = from_decimal_to_big_decimal(value_1);
  big_dec big_val_2 = from_decimal_to_big_decimal(value_2);
  big_dec tmp_res;

  for (int i = 0; i < (BIG_SIZE - 1) * 32; i++) {
    big_dec buffer = big_result;
    for (int j = 0; j < (BIG_SIZE - 1) * 32; j++) {
      int res_bit = big_get_bit(big_val_1, i) * big_get_bit(big_val_2, j);
      big_set_bit(&tmp_res, j, res_bit);
    }
    big_shift_left(&tmp_res, i);
    big_summ(buffer, tmp_res, &big_result);
  }
  big_set_scale(&big_result, scale_1 + scale_2);
  if (sign_1 != sign_2) big_invert_sign(&big_result);
  error = from_big_decimal_to_decimal(big_result, result);
  return error;
}

// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   int error = 0;
//   big_dec big_result;
//   big_decimal_zero(&big_result);
//   int sign_1 = get_sign(value_1);
//   int sign_2 = get_sign(value_2);
//   int scale_1 = get_scale(value_1);
//   int scale_2 = get_scale(value_2);
//   big_dec big_val_1 = from_decimal_to_big_decimal(value_1);
//   big_dec big_val_2 = from_decimal_to_big_decimal(value_2);
//   big_dec temp;

//   do {
//   } while (s21_is_greater(value_1, value_2));

//   return error;
// }