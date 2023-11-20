#ifndef S21_MATH
#define S21_MATH

#include <stdio.h>
#include <stdlib.h>

#define S21_NAN 0.0 / 0.0
#define S21_INF_POS 1.0 / 0.0L
#define S21_INF_NEG -1.0 / 0.0L

int s21_abs(int x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_ceil(double x);

#endif