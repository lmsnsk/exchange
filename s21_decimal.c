#include "s21_decimal.h"

int main() {
  printf("%lu\n",
         0b1111111111111111111111111111111111111111111111111111111111111111);
  return 0;
}

void s21_decimal_zero(s21_decimal *dst) {
  for (int i = 0; i < 4; i++) dst->bits[i] = 0;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int code = 0;
  s21_decimal_zero(dst);
  if (src < 0) {
    s21_invert_sign(dst);  // sign -
    src = -src;
  }
  if (src > __INT_MAX__) code = 1;
  if (!code) dst->bits[0] = src;
  return code;
}

void s21_invert_sign(s21_decimal *dst) { dst->bits[3] *= -1; }

int s21_sum(s21_decimal *dst1, s21_decimal *dst2) {
  long subsum1 = dst1->bits[0] + dst2->bits[0];
  long subsum2 = dst1->bits[1] + dst2->bits[1];
  long subsum3 = dst1->bits[2] + dst2->bits[2];
  if (subsum1 > __INT_MAX__) subsum2 += 1;
  if (subsum2 > __INT_MAX__) subsum3 += 1;
  return 0;
}