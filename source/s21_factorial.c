#include "s21_math.h"

long double s21_factorial(int x) {
  long double res;
  if (x < 2) return x < 0 ? 0 : 1;
  return res = x * s21_factorial(x - 1);
}

// int main() {
//   long double a = s21_factorial(-5);
//   printf("---%Lf\n", a);
//   return 0;
// }