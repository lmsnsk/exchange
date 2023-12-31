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
  int error = check_decimal(src);

  if (!error) {
    int sign = get_sign(src);
    unsigned scale = get_scale(src);

    if (scale) {
      big_dec big_temp = from_decimal_to_big_decimal(src);
      big_dec ten_big_decimal = from_int_to_big_decimal(10);

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

void convert_float_to_decimal(float src, s21_decimal *dst, int *error,
                              int sign) {
  double mantissa;
  int exp;
  char float_str[50];
  sprintf(float_str, "%E", src);
  char *exp_str = strchr(float_str, 'E');
  exp_str += 2;
  sscanf(exp_str, "%d", &exp);
  float_str[8] = 0;
  sscanf(float_str, "%lf", &mantissa);
  if (exp > 28) {
    *error = 1;
  } else {
    int counter = 0;
    double mantissa_temp = mantissa;
    for (int i = 0; i < 6; i++) {
      if (mantissa_temp != (int)mantissa_temp) counter++;
      mantissa_temp *= 10;
    }
    null_decimal(dst);
    dst->bits[0] = (int)(mantissa * pow(10, counter));
    set_scale(dst, counter);
    if (sign) invert_sign(dst);

    big_dec big_dst = from_decimal_to_big_decimal(*dst);
    big_dec ten_big_decimal = from_int_to_big_decimal(10);

    for (int i = 0; i < exp; i++) {
      if (counter) {
        big_set_scale(&big_dst, counter - 1);
        counter--;
      } else {
        big_dst = big_mul(big_dst, ten_big_decimal);
      }
    }
    *error = from_big_decimal_to_decimal(big_dst, dst);
    if (*error) *error = 1;
  }
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
    convert_float_to_decimal(src, dst, &error, sign);
  }
  return error;
}

int is_bits_1_2_empty(s21_decimal src) {
  int res = 0;
  if (src.bits[1] == 0 && src.bits[2] == 0) res = 1;
  return res;
}

double convert_to_float(s21_decimal src, unsigned scale, int sign) {
  double dst;
  dst = (double)(unsigned)src.bits[0];
  if (scale) dst /= pow(10, scale);
  if (sign) dst *= -1;
  return dst;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = check_decimal(src);
  if (!error) {
    int sign = get_sign(src);
    unsigned scale = get_scale(src);
    int check_bits = is_bits_1_2_empty(src);

    if (check_bits) {
      *dst = (float)convert_to_float(src, scale, sign);
    } else {
      int count = 0;
      big_dec big_res, big_temp;
      big_dec big_src = from_decimal_to_big_decimal(src);
      big_dec big_ten_decimal = from_int_to_big_decimal(10);
      big_temp = big_src;

      while (!check_bits) {
        big_div_ten(&big_res, &big_temp, big_ten_decimal);
        from_big_decimal_to_decimal(big_res, &src);
        check_bits = is_bits_1_2_empty(src);
        big_temp = big_res;
        count++;
      }
      double value = convert_to_float(src, scale, sign);
      *dst = (float)(value * pow(10, count));
    }
  }
  return error;
}