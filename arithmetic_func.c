#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
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

  if (sign_1 == sign_2) {
    big_summ(big_val_1, big_val_2, &big_result);
    if (sign_1) big_invert_sign(&big_result);
  } else {
    big_diff(big_val_1, big_val_2, &big_result);
    // otnimaen iz b m i stavim znak b
  }
  big_set_scale(&big_result, scale_1 > scale_2 ? scale_1 : scale_2);

  error = from_big_decimal_to_decimal(big_result, result);

  return error;
}