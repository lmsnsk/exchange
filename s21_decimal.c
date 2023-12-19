#include "s21_decimal.h"

int main() {
  s21_decimal example;
  decimal_zero(&example);
  s21_from_int_to_decimal(500, &example);

  printf("%u\n", example.bits[0]);
  printf("%u\n", example.bits[1]);
  printf("%u\n", example.bits[2]);
  printf("%u\n", example.bits[3]);
  return 0;
}

void decimal_zero(s21_decimal *dst) {
  for (int i = 0; i < 4; i++) dst->bits[i] = 0;
}

void invert_sign(s21_decimal *dst) {
  if (dst->bits[3] == 0) {
    dst->bits[3] = 1;
    dst->bits[3] <<= 31;
  } else
    dst->bits[3] = ~(dst->bits[3]) + 1;
}

int get_sign(s21_decimal dst) { return (dst.bits[3] & MASK) >> 31; }

int get_bit(s21_decimal dst, unsigned pos) {
  int bit = -1;
  int val = pow(2, pos);
  if (pos < 32) {
    bit = (dst.bits[0] & val) >> pos;
  } else if (32 >= pos && pos < 64) {
    bit = (dst.bits[1] & val) >> pos;
  } else if (pos < 96) {
    bit = (dst.bits[2] & val) >> pos;
  } else if (pos < 128) {
    bit = (dst.bits[3] & val) >> pos;
  }
  return bit;
};

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int code = 0, sign = 0;
  decimal_zero(dst);
  if (src < 0) {
    src = -src;
    sign = 1;
  }
  if (src > __INT_MAX__) code = 1;
  if (!code) dst->bits[0] = src;
  if (sign) invert_sign(dst);
  return code;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  decimal_zero(result);
  invert_sign(&value);
  int code = 0;  // ??
  for (int i = 0; i < 4; i++) result->bits[i] = value.bits[i];
  return code;
}
