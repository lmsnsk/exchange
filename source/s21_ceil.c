#include "s21_math.h"

long double s21_ceil(double x) {
  long double res;
  if (x == S21_NAN) res = S21_NAN;
  if (x == S21_INF_NEG) res = S21_INF_NEG;
  if (x == S21_INF_POS) res = S21_INF_POS;
  if (x != S21_NAN && x != S21_INF_NEG && x != S21_INF_POS)
    res = (long long int)x;
  if (x > 0) res++;
  return res;
}