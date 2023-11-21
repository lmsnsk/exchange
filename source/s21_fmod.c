#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double res;
  long double n;
  if (x != x || y != y) {
    res = S21_NAN;
  } else if (x == S21_INF_NEG && y != 0) {
    res = S21_INF_NEG;
  } else if (x == S21_INF_POS && y != 0) {
    res = S21_INF_POS;
  } else if (y == 0) {
    res = S21_NAN;
  } else {
    n = x / y;
    res = x - y * (long long int)n;
  }
  return res;
}