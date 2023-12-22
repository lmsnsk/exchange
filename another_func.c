#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = check_decimal(value);
  if (!error) {
    decimal_zero(result);
    invert_sign(&value);
    for (int i = 0; i < 4; i++) result->bits[i] = value.bits[i];
  }
  return error;
}