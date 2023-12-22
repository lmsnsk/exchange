#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = check_decimal(value);
  if (!error) {
    decimal_zero(result);
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
      decimal_zero(result);

      for (int i = 0; i < (96 - scale); i++) {  ///////// NEVERNO!
        int bit = get_bit(value, i + scale);
        set_bit(result, i, bit);
      }
      for (int i = 0; i < scale; i++) {
        if (get_bit(value, i)) flag = 1;
      }
      if (flag && sign) result->bits[0] -= 1;
    }
  }
  return error;
}