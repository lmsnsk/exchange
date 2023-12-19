#ifndef S21_DECIMAL
#define S21_DECIMAL
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MASK 0x80000000

typedef struct {
  int bits[4];
} s21_decimal;

int get_sign(s21_decimal dst);
int get_bit(s21_decimal dst, unsigned pos);
void invert_sign(s21_decimal *dst);
void decimal_zero(s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif
