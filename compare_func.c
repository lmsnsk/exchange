#include "s21_decimal.h"

int big_is_greater(big_dec value_1, big_dec value_2) {
  int comp = 0;
  for (int i = (BIG_SIZE - 1) * 32 - 1; i >= 0; i--) {
    comp = big_get_bit(value_1, i) - big_get_bit(value_2, i);
    if (comp) break;
  }
  return comp;
}

int compare(s21_decimal value_1, s21_decimal value_2) {
  int comp = 0;
  big_dec big_val_1 = from_decimal_to_big_decimal(value_1);
  big_dec big_val_2 = from_decimal_to_big_decimal(value_2);
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);

  if (!is_decimal_zero(value_1) || !is_decimal_zero(value_2)) {
    if (!sign_1 && sign_2) {
      comp = 1;
    } else if (sign_1 && !sign_2) {
      comp = -1;
    } else {
      int scale_1 = get_scale(value_1);
      int scale_2 = get_scale(value_2);

      if (scale_1 > scale_2)
        big_normalization(&big_val_2, scale_1 - scale_2);
      else if (scale_1 < scale_2)
        big_normalization(&big_val_1, scale_2 - scale_1);

      comp = big_is_greater(big_val_1, big_val_2);
      if (sign_1) comp *= -1;
    }
  }
  return comp;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int comp = compare(value_1, value_2);
  int result = comp == 1 ? 1 : 0;
  return result;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int comp = compare(value_1, value_2);
  int result = comp >= 0 ? 1 : 0;
  return result;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int comp = compare(value_1, value_2);
  int result = comp == -1 ? 1 : 0;
  return result;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int comp = compare(value_1, value_2);
  int result = comp <= 0 ? 1 : 0;
  return result;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = compare(value_1, value_2);
  result = result ? 0 : 1;
  return result;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = compare(value_1, value_2);
  result = result ? 1 : 0;
  return result;
}