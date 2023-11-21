#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double res;
  if (x != x || y != y)
    res = S21_NAN;
  else if (x == S21_INF_NEG && y != 0)
    res = S21_INF_NEG;
  else if (x == S21_INF_POS && y != 0)
    res = S21_INF_POS;
  if (x < 0 && res != x) res--;
  return res;
}