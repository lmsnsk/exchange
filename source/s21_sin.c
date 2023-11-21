#include "s21_math.h"

long double s21_sin(double x) {
  long double res = 0;
  long double pow = 1;
  long double fault = 0;
  int minus = 1;
  if (x != x)
    res = S21_NAN;
  else if (x == S21_INF_NEG)
    res = S21_NAN;
  else if (x == S21_INF_POS)
    res = S21_NAN;
  else {
    while (s21_fabs(x) > 2 * S21_PI) {
      x += 2 * S21_PI * x / s21_fabs(x) * -1;
    }
    for (int i = 0; i < 100; i++) {
      fault = (minus * pow * x) / s21_factorial(i * 2 + 1);
      res += fault;
      minus = -minus;
      pow = pow * x * x;
    }
  }
  return res;
}