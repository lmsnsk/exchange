#include "s21_math.h"

long double s21_floor(double x) {
  long double res;
  if (x == S21_NAN) res = x;
  if (x != S21_NAN) res = (int)x;
  if (x < 0) res--;
  return res;
}