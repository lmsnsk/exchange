#include "s21_decimal.h"

void summ(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int memory = 0;
  for (int i = 0; i < 3 * 32; i++) {
    unsigned res = get_bit(value_1, i) + get_bit(value_2, i) + memory;
    memory = res / 2;
    res %= 2;
    set_bit(result, i, res);
  }
}

void big_summ(big_dec value_1, big_dec value_2, big_dec *result) {
  int memory = 0;
  for (int i = 0; i < (BIG_SIZE - 1) * 32; i++) {
    unsigned res = big_get_bit(value_1, i) + big_get_bit(value_2, i) + memory;
    memory = res / 2;
    res %= 2;
    big_set_bit(result, i, res);
  }
}

void diff(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int memory = 0;
  for (int i = 0; i < 3 * 32; i++) {
    int res = get_bit(value_1, i) - get_bit(value_2, i) - memory;
    memory = res < 0 ? 1 : 0;
    res %= 2;

    set_bit(result, i, res);
  }
}

void big_diff(big_dec value_1, big_dec value_2, big_dec *result) {
  int memory = 0;
  for (int i = 0; i < (BIG_SIZE - 1) * 32; i++) {
    int res = big_get_bit(value_1, i) - big_get_bit(value_2, i) - memory;
    memory = res < 0 ? 1 : 0;
    res %= 2;

    big_set_bit(result, i, res);
  }
}

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

  if (sign_1) big_invert_sign(&big_val_1);
  if (sign_2) big_invert_sign(&big_val_2);

  if (abs(sign_1 - sign_2) == is_sub) {
    big_summ(big_val_1, big_val_2, &big_result);
    if (sign_1) big_invert_sign(&big_result);
  } else {
    if (!big_is_greater(big_val_1, big_val_2)) {
      big_null_decimal(&big_result);
    } else {
      if (big_is_greater(big_val_1, big_val_2) > 0) {
        big_diff(big_val_1, big_val_2, &big_result);
        if (sign_1) big_invert_sign(&big_result);
      } else {
        big_diff(big_val_2, big_val_1, &big_result);
        if (is_sub) big_invert_sign(&big_result);
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
    for (int k = 0; k < i; k++) big_shift_left(&tmp_res, 1);
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

void big_res_and_remainder(big_dec *big_result, big_dec delitel,
                           big_dec *remainder) {
  big_dec temp = delitel;
  big_dec temp_for_compare = delitel;
  int count = -1;

  while (big_is_greater(*remainder, temp) >= 0) {
    big_shift_left(&temp_for_compare, 1);
    count++;
    if (big_is_greater(temp_for_compare, *remainder) >= 0) break;
    big_shift_left(&temp, 1);
  }

  while (count + 1) {
    temp = delitel;
    for (int k = 0; k < count; k++) big_shift_left(&temp, 1);

    if (big_is_greater(temp, *remainder) > 0) {
      big_shift_left(big_result, 1);
    } else {
      big_diff(*remainder, temp, remainder);
      big_shift_left(big_result, 1);
      big_set_bit(big_result, 0, ONE);
    }
    count--;
  }
}

void big_div_ten(big_dec *big_result, big_dec *remainder,
                 big_dec big_ten_decimal) {
  big_null_decimal(big_result);
  big_res_and_remainder(big_result, big_ten_decimal, remainder);
}

void big_div(big_dec *big_val_1, big_dec *big_val_2, big_dec *big_result,
             big_dec big_ten_decimal, int *scale) {
  big_dec remainder = *big_val_1;

  for (int i = 0; !big_is_decimal_zero(remainder); i++) {
    big_dec buffer_big_result;
    big_null_decimal(&buffer_big_result);
    if (i) {
      remainder = big_mul(remainder, big_ten_decimal);
      *big_result = big_mul(*big_result, big_ten_decimal);
      *scale += 1;
    }
    big_res_and_remainder(&buffer_big_result, *big_val_2, &remainder);
    big_summ(*big_result, buffer_big_result, big_result);
    if (*scale == 28) break;
  }
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  null_decimal(result);
  if (is_decimal_zero(value_2)) error = 3;

  if (!error && !is_decimal_zero(value_1)) {
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

    while (big_is_greater(big_val_1, big_val_2) < 0) {
      if (scale_1 > 28) break;
      big_val_1 = big_mul(big_val_1, ten_big_decimal);
      scale_1++;
    }

    if (big_is_greater(big_val_1, big_val_2)) {
      big_div(&big_val_1, &big_val_2, &big_result, ten_big_decimal, &scale_1);
    } else {
      big_result.bits[0] = 1;
    }

    if (sign_1 != sign_2) big_invert_sign(&big_result);
    int res_scale = scale_1 - scale_2;
    while (res_scale < 0) {
      big_result = big_mul(big_result, ten_big_decimal);
      res_scale++;
    }
    big_set_scale(&big_result, res_scale);
    error = from_big_decimal_to_decimal(big_result, result);
  }
  return error;
}