#ifndef S21_DECIMAL
#define S21_DECIMAL
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SCALE_MASK 0xff0000
#define BIG_SIZE 8

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  unsigned bits[BIG_SIZE];
} big_dec;

typedef enum { ZERO, ONE } bit_type;

// TEST FUNCTIONS /////////////////////////////
void print_dec(s21_decimal dec);
void print_big_dec(big_dec dec);

// --- support functions --- //
void decimal_zero(s21_decimal *dst);
void big_decimal_zero(big_dec *dst);
int get_sign(s21_decimal value);
int big_get_sign(big_dec value);
void invert_sign(s21_decimal *dst);
void big_invert_sign(big_dec *dst);
int get_bit(s21_decimal value, unsigned pos);
int big_get_bit(big_dec value, unsigned pos);
void set_bit(s21_decimal *dst, unsigned pos, bit_type bit);
void big_set_bit(big_dec *dst, unsigned pos, bit_type bit);
int get_scale(s21_decimal value);
int big_get_scale(big_dec value);
void set_scale(s21_decimal *dst, unsigned scale);
void big_set_scale(big_dec *dst, unsigned scale);
int check_parity(int *value, int offset);
int check_decimal(s21_decimal value);
big_dec from_decimal_to_big_decimal(s21_decimal value);
int from_big_decimal_to_decimal(big_dec value, s21_decimal *result);
void shift_left(s21_decimal *dst, int shift);
void big_shift_left(big_dec *dst, int shift);
void summ(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void big_summ(big_dec value_1, big_dec value_2, big_dec *result);
void diff(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void big_diff(big_dec value_1, big_dec value_2, big_dec *result);
void normalization(s21_decimal *dst, int diff);
void big_normalization(big_dec *dst, int diff);

// --- arithmetic functions --- //
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// --- transform functions --- //
int s21_from_int_to_decimal(int src, s21_decimal *dst);

// --- another functions --- //
int s21_negate(s21_decimal value, s21_decimal *result);

#endif
