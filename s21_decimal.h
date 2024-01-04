#ifndef S21_DECIMAL
#define S21_DECIMAL
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  ///

#define SCALE_MASK 0xff0000
#define MINUS_MAX_INT -2147483648
#define MAX_SCALE 28
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
void null_decimal(s21_decimal *dst);
void big_null_decimal(big_dec *dst);
int is_decimal_zero(s21_decimal value);
int big_is_decimal_zero(big_dec value);
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
float random_float(float a, float b);
big_dec from_decimal_to_big_decimal(s21_decimal value);
int from_big_decimal_to_decimal(big_dec value, s21_decimal *result);
void shift_left(s21_decimal *dst, int shift);
void big_shift_left(big_dec *dst, int shift);
void big_normalization(big_dec *dst, int diff);
void bank_round(big_dec *value, big_dec remainder);
int is_big(big_dec value);

// --- arithmetic functions --- //
void summ(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void big_summ(big_dec value_1, big_dec value_2, big_dec *result);
void diff(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void big_diff(big_dec value_1, big_dec value_2, big_dec *result);
int add_and_sub_core(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result, int check_add_or_sub);
big_dec big_mul(big_dec big_val_1, big_dec big_val_2);
void big_div(big_dec *big_val_1, big_dec *big_val_2, big_dec *big_result,
             big_dec big_ten_decimal, int *scale);
void big_div_ten(big_dec *big_result, big_dec *remainder,
                 big_dec big_ten_decimal);
void big_res_and_remainder(big_dec *big_result, big_dec delitel,
                           big_dec *remainder);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// --- transform functions --- //
big_dec from_int_to_big_decimal(int src);
int convert_decimal_to_int(s21_decimal src, int *dst, int sign);
int is_bits_1_2_empty(s21_decimal src);
double convert_to_float(s21_decimal src, unsigned scale, int sign);
void convert_float_to_decimal(float src, s21_decimal *dst, int *error,
                              int sign);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// --- another functions --- //
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// --- compare functions --- //
int big_is_greater(big_dec value_1, big_dec value_2);
int compare(s21_decimal value_1, s21_decimal value_2);

int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

#endif  // S21_DECIMAL
