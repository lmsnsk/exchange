#include "s21_decimal.h"

big_dec from_int_to_big_decimal(int src) {
  big_dec dst;
  int sign = 0;
  big_null_decimal(&dst);
  if (src < 0) {
    src = -src;
    sign = 1;
  }
  dst.bits[0] = src;
  if (sign) big_invert_sign(&dst);
  return dst;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0, sign = 0;
  null_decimal(dst);
  if (src < 0) {
    src = -src;
    sign = 1;
  }
  if (src > __INT_MAX__) error = 1;
  if (!error) {
    dst->bits[0] = src;
    if (sign) invert_sign(dst);
  }
  return error;
}

int convert_decimal_to_int(s21_decimal src, int *dst, int sign) {
  int error = 0;
  if (src.bits[1] == 0 && src.bits[2] == 0) {
    if (src.bits[0] < 0 && src.bits[0] != MINUS_MAX_INT) {
      error = 1;
    } else {
      *dst = src.bits[0];
      if (sign && src.bits[0] != MINUS_MAX_INT) *dst *= -1;
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  if (check_decimal(src)) error = 1;

  if (!error) {
    int sign = get_sign(src);
    unsigned scale = get_scale(src);

    if (scale) {
      big_dec big_temp = from_decimal_to_big_decimal(src);
      s21_decimal ten_decimal;
      s21_from_int_to_decimal(10, &ten_decimal);
      big_dec ten_big_decimal = from_decimal_to_big_decimal(ten_decimal);

      while (scale > 0) {
        big_dec remainder = big_temp;
        big_div_ten(&big_temp, &remainder, ten_big_decimal);
        scale--;
      }
      from_big_decimal_to_decimal(big_temp, &src);
    }
    error = convert_decimal_to_int(src, dst, sign);
  }
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0, sign = 0;
  if (src < 0) {
    src = -src;
    sign = 1;
  }
  if (src != src || src > 2E96) error = 1;
  if (src < 1E-28 && src != 0) {
    null_decimal(dst);
    error = 1;
  }
  if (!error) {
    double mantissa;
    int scale;
    char float_str[50];
    sprintf(float_str, "%E", src);
    char *exp_str = strchr(float_str, 'E');
    exp_str += 2;
    sscanf(exp_str, "%d", &scale);
    float_str[8] = 0;
    sscanf(float_str, "%lf", &mantissa);
    if ((scale == 28 && mantissa > 7.922816) || scale > 28) {
      error = 1;
    } else {
      null_decimal(dst);
      dst->bits[0] = (int)(mantissa * 1E6);
      set_scale(dst, scale);
      if (sign) invert_sign(dst);
    }
  }
  return error;
}