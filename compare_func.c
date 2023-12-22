#include "s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int result;

  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);

  if (!sign_1 && sign_2) {
    result = 1;
  } else if (sign_1 && !sign_2) {
    result = 0;
  } else {
    int scale_1 = get_scale(value_1);
    int scale_2 = get_scale(value_2);

    if (scale_1 > scale_2)
      normalization(&value_2, scale_1 - scale_2);
    else if (scale_1 != scale_2)
      normalization(&value_1, scale_2 - scale_1);

    ;
  }

  return result;
}