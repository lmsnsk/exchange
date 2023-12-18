#ifndef S21_DECIMAL
#define S21_DECIMAL
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int bits[4];
} s21_decimal;

void s21_decimal_zero(s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
void s21_invert_sign(s21_decimal *dst);

#endif
