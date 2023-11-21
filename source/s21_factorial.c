// #include <math.h>

#include "s21_math.h"

long double s21_factorial(int x) {
  long double res;
  if (x < 2) return x < 0 ? 0 : 1;
  return res = x * s21_factorial(x - 1);
}

// int main() {
//   long double a = s21_factorial(-5);
//   printf("---%Lf\n", a);
//   printf("%f\n", floor(0.0 / 0.0));
//   printf("%Lf\n", s21_floor(0.0 / 0.0));
//   return 0;
// }

// long double s21_floor(double x) {
//   long double res;
//   if (x != x)
//     res = S21_NAN;
//   else if (x == S21_INF_NEG)
//     res = S21_INF_NEG;
//   else if (x == S21_INF_POS)
//     res = S21_INF_POS;
//   else
//     res = (long long int)x;
//   if (x < 0) res--;
//   return res;
// }