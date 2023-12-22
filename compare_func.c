#include "s21_decimal.h"

int is_greater_or_not(s21_decimal value_1, s21_decimal value_2, int *result,
                      int *temp, int sign_1, int val) {
  int compare = 0;
  int sign_2 = get_sign(value_2);

  if (!sign_1 && sign_2) {
    *result = val ? 0 : 1;
  } else if (sign_1 && !sign_2) {
    *result = val;
  } else {
    int scale_1 = get_scale(value_1);
    int scale_2 = get_scale(value_2);

    if (scale_1 > scale_2)
      normalization(&value_2, scale_1 - scale_2);
    else if (scale_1 != scale_2)
      normalization(&value_1, scale_2 - scale_1);

    for (int i = 95; i >= 0; i--) {
      compare = get_bit(value_1, i) - get_bit(value_2, i);
      if (compare) break;
    }
    *temp = 1;
  }
  return compare;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int result, temp = 0;
  int sign_1 = get_sign(value_1);
  int compare = is_greater_or_not(value_1, value_2, &result, &temp, sign_1, 0);
  if (temp) {
    if (!sign_1)
      result = compare > 0 ? 1 : 0;
    else
      result = compare >= 0 ? 0 : 1;
  }
  return result;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result, temp = 0;
  int sign_1 = get_sign(value_1);
  int compare = is_greater_or_not(value_1, value_2, &result, &temp, sign_1, 0);
  if (temp) {
    if (!sign_1)
      result = compare >= 0 ? 1 : 0;
    else
      result = compare > 0 ? 0 : 1;
  }
  return result;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result, temp = 0;
  int sign_1 = get_sign(value_1);
  int compare = is_greater_or_not(value_1, value_2, &result, &temp, sign_1, 1);
  if (temp) {
    if (!sign_1)
      result = compare < 0 ? 1 : 0;
    else
      result = compare <= 0 ? 0 : 1;
  }
  return result;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result, temp = 0;
  int sign_1 = get_sign(value_1);
  int compare = is_greater_or_not(value_1, value_2, &result, &temp, sign_1, 1);
  if (temp) {
    if (!sign_1)
      result = compare <= 0 ? 1 : 0;
    else
      result = compare < 0 ? 0 : 1;
  }
  return result;
}

int is_equal_or_not(s21_decimal value_1, s21_decimal value_2, int val) {
  int result = val ? 0 : 1;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);

  if (sign_1 != sign_2) {
    result = val;
  } else {
    int scale_1 = get_scale(value_1);
    int scale_2 = get_scale(value_2);

    if (scale_1 > scale_2)
      normalization(&value_2, scale_1 - scale_2);
    else if (scale_1 != scale_2)
      normalization(&value_1, scale_2 - scale_1);

    for (int i = 95; i >= 0; i--) {
      if (get_bit(value_1, i) != get_bit(value_2, i)) {
        result = val;
        break;
      }
    }
  }
  return result;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = is_equal_or_not(value_1, value_2, 0);
  return result;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = is_equal_or_not(value_1, value_2, 1);
  return result;
}