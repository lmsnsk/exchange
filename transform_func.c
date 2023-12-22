#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0, sign = 0;
  decimal_zero(dst);
  if (src < 0) {
    src = -src;
    sign = 1;
  }
  if (src > __INT_MAX__) error = 1;
  if (!error) {
    dst->bits[0] = src;
    if (sign) invert_sign(dst);
  }
  return error;
}
