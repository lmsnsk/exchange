#include "s21_decimal.h"

int main() {
  printf("\n");
  return 0;
}

void s21_decimal_zero(s21_decimal *dst) {
  for (int i = 0; i < 4; i++) dst->bits[i] = 0;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int code = 0;
  s21_decimal_zero(dst);
  if (src < 0) {
    ;  // sign -
    src = -src;
  }
  if (src > __INT_MAX__) code = 1;
  if (!code) dst->bits[0] = src;
  return code;
}
