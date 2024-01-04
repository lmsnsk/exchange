#include "s21_decimal.h"

void null_decimal(s21_decimal *dst) {
  for (int i = 0; i < 4; i++) dst->bits[i] = 0;
}

void big_null_decimal(big_dec *dst) {
  for (int i = 0; i < BIG_SIZE; i++) dst->bits[i] = 0;
}

int is_decimal_zero(s21_decimal value) {
  int is_zero = 1;
  for (int i = 0; i < 3; i++)
    if (value.bits[i] != 0) is_zero = 0;
  return is_zero;
}

int big_is_decimal_zero(big_dec value) {
  int is_zero = 1;
  for (int i = 0; i < BIG_SIZE - 1; i++)
    if (value.bits[i] != 0) is_zero = 0;
  return is_zero;
}

int get_sign(s21_decimal value) { return get_bit(value, 127); }

int big_get_sign(big_dec value) {
  return big_get_bit(value, BIG_SIZE * 32 - 1);
}

void invert_sign(s21_decimal *dst) {
  int sign = get_sign(*dst);
  set_bit(dst, 127, sign ? ZERO : ONE);
}

void big_invert_sign(big_dec *dst) {
  int sign = big_get_sign(*dst);
  big_set_bit(dst, 255, sign ? ZERO : ONE);
}

int get_bit(s21_decimal value, unsigned pos) {
  int bit = 0;
  unsigned val, i = 32;
  if (pos < i) {
    val = pow(2, pos);
    bit = (value.bits[0] & val) >> pos;
  } else if (pos < i * 2) {
    val = pow(2, pos - i);
    bit = (value.bits[1] & val) >> (pos - i);
  } else if (pos < i * 3) {
    val = pow(2, pos - i * 2);
    bit = (value.bits[2] & val) >> (pos - i * 2);
  } else if (pos < i * 4) {
    val = pow(2, pos - i * 3);
    bit = (value.bits[3] & val) >> (pos - i * 3);
  }
  return bit;
};

int big_get_bit(big_dec value, unsigned pos) {
  int bit = 0;
  unsigned val, i = 32;
  if (pos < i) {
    val = pow(2, pos);
    bit = (value.bits[0] & val) >> pos;
  } else if (pos < i * 2) {
    val = pow(2, pos - i);
    bit = (value.bits[1] & val) >> (pos - i);
  } else if (pos < i * 3) {
    val = pow(2, pos - i * 2);
    bit = (value.bits[2] & val) >> (pos - i * 2);
  } else if (pos < i * 4) {
    val = pow(2, pos - i * 3);
    bit = (value.bits[3] & val) >> (pos - i * 3);
  } else if (pos < i * 5) {
    val = pow(2, pos - i * 4);
    bit = (value.bits[4] & val) >> (pos - i * 4);
  } else if (pos < i * 6) {
    val = pow(2, pos - i * 5);
    bit = (value.bits[5] & val) >> (pos - i * 5);
  } else if (pos < i * 7) {
    val = pow(2, pos - i * 6);
    bit = (value.bits[6] & val) >> (pos - i * 6);
  } else if (pos < i * 8) {
    val = pow(2, pos - i * 7);
    bit = (value.bits[7] & val) >> (pos - i * 7);
  }
  return bit;
};

void set_bit(s21_decimal *dst, unsigned pos, bit_type bit) {
  unsigned val, i = 32;
  if (pos < i) {
    val = pow(2, pos);
    dst->bits[0] = bit ? dst->bits[0] | val : dst->bits[0] & ~val;
  } else if (pos < i * 2) {
    val = pow(2, pos - i);
    dst->bits[1] = bit ? dst->bits[1] | val : dst->bits[1] & ~val;
  } else if (pos < i * 3) {
    val = pow(2, pos - i * 2);
    dst->bits[2] = bit ? dst->bits[2] | val : dst->bits[2] & ~val;
  } else if (pos < i * 4) {
    val = pow(2, pos - i * 3);
    dst->bits[3] = bit ? dst->bits[3] | val : dst->bits[3] & ~val;
  }
}

void big_set_bit(big_dec *dst, unsigned pos, bit_type bit) {
  unsigned val, i = 32;
  if (pos < i) {
    val = pow(2, pos);
    dst->bits[0] = bit ? dst->bits[0] | val : dst->bits[0] & ~val;
  } else if (pos < i * 2) {
    val = pow(2, pos - i);
    dst->bits[1] = bit ? dst->bits[1] | val : dst->bits[1] & ~val;
  } else if (pos < i * 3) {
    val = pow(2, pos - i * 2);
    dst->bits[2] = bit ? dst->bits[2] | val : dst->bits[2] & ~val;
  } else if (pos < i * 4) {
    val = pow(2, pos - i * 3);
    dst->bits[3] = bit ? dst->bits[3] | val : dst->bits[3] & ~val;
  } else if (pos < i * 5) {
    val = pow(2, pos - i * 4);
    dst->bits[4] = bit ? dst->bits[4] | val : dst->bits[4] & ~val;
  } else if (pos < i * 6) {
    val = pow(2, pos - i * 5);
    dst->bits[5] = bit ? dst->bits[5] | val : dst->bits[5] & ~val;
  } else if (pos < i * 7) {
    val = pow(2, pos - i * 6);
    dst->bits[6] = bit ? dst->bits[6] | val : dst->bits[6] & ~val;
  } else if (pos < i * 8) {
    val = pow(2, pos - i * 7);
    dst->bits[7] = bit ? dst->bits[7] | val : dst->bits[7] & ~val;
  }
}

int get_scale(s21_decimal value) {
  value.bits[3] &= SCALE_MASK;
  return value.bits[3] >> 16;
};

int big_get_scale(big_dec value) {
  value.bits[BIG_SIZE - 1] &= SCALE_MASK;
  return value.bits[BIG_SIZE - 1] >> 16;
};

void set_scale(s21_decimal *dst, unsigned scale) {
  int sign = get_sign(*dst);
  dst->bits[3] = 0;
  dst->bits[3] >>= 16;
  dst->bits[3] |= scale;
  dst->bits[3] <<= 16;
  if (sign) invert_sign(dst);
};

void big_set_scale(big_dec *dst, unsigned scale) {
  int sign = big_get_sign(*dst);
  dst->bits[BIG_SIZE - 1] = 0;
  dst->bits[BIG_SIZE - 1] >>= 16;
  dst->bits[BIG_SIZE - 1] |= scale;
  dst->bits[BIG_SIZE - 1] <<= 16;
  if (sign) big_invert_sign(dst);
};

int check_parity(int *value, int offset) {
  int error = 0;
  for (int i = 0; i < offset; i++) {
    if (*value % 2) {
      error = 1;
      break;
    }
    *value >>= 1;
  }
  return error;
}

int check_decimal(s21_decimal value) {
  int error = check_parity(&value.bits[3], 16);
  if (!error) {
    value.bits[3] >>= 8;
    error = check_parity(&value.bits[3], 7);
  }
  return error;
}

float random_float(float a, float b) {
  float m = (float)rand() / RAND_MAX;
  float num = a + m * (b - a);
  return num;
}

big_dec from_decimal_to_big_decimal(s21_decimal value) {
  big_dec result;

  for (int i = 0; i < 3; i++) result.bits[i] = value.bits[i];
  result.bits[BIG_SIZE - 1] = value.bits[3];

  for (int i = 3; i < (int)(BIG_SIZE - 1); i++) result.bits[i] = 0;

  return result;
}

int is_big(big_dec value) {
  int big = 0;
  for (int i = 3; i < BIG_SIZE - 1; i++) {
    if (value.bits[i] != 0) {
      big = 1;
      break;
    }
  }
  return big;
}

int from_big_decimal_to_decimal(big_dec value, s21_decimal *result) {
  int error = 0;
  int sign = big_get_sign(value);
  unsigned scale = big_get_scale(value);
  big_dec big_result = value;

  if (is_big(big_result)) {
    if (!scale) {
      error = sign ? 2 : 1;
    } else {
      s21_decimal ten_decimal;
      s21_from_int_to_decimal(10, &ten_decimal);
      big_dec ten_big_decimal = from_decimal_to_big_decimal(ten_decimal);

      while (is_big(big_result) && scale > 0) {
        big_dec remainder = big_result;
        big_div_ten(&big_result, &remainder, ten_big_decimal);
        bank_round(&big_result, remainder);
        scale--;
      }

      if (is_big(big_result)) {
        error = sign ? 2 : 1;
      } else {
        big_set_scale(&big_result, scale);
        if (sign) big_invert_sign(&big_result);
      }
    }
  }
  if (!error) {
    for (int i = 0; i < 3; i++) result->bits[i] = big_result.bits[i];
    result->bits[3] = big_result.bits[BIG_SIZE - 1];
  }
  return error;
}

void big_shift_left(big_dec *dst, int shift) {
  if (shift) {
    unsigned mem = 0;
    for (int i = 0; i < BIG_SIZE - 1; i++) {
      unsigned tmp = dst->bits[i];
      dst->bits[i] <<= shift;
      dst->bits[i] |= mem;  /// ?
      mem = tmp >> (32 - shift);
    }
  }
}

void big_normalization(big_dec *dst, int diff) {
  unsigned scale = big_get_scale(*dst);
  for (int i = 0; i < diff; i++) {
    big_dec tmp1 = *dst;
    big_dec tmp2 = *dst;
    big_shift_left(&tmp1, 1);
    big_shift_left(&tmp2, 3);
    big_summ(tmp1, tmp2, dst);
  }
  big_set_scale(dst, scale + diff);
}

void bank_round(big_dec *value, big_dec remainder) {
  if (remainder.bits[0] > 5) {
    value->bits[0] += 1;
  } else if (remainder.bits[0] == 5) {
    if (big_get_bit(*value, 0)) value->bits[0] += 1;
  }
}
