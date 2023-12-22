#include "s21_decimal.h"

// void print_dec(s21_decimal dec);
// void print_big_dec(big_dec dec);

int main() {
  s21_decimal result;
  s21_decimal example1;
  s21_decimal example2;
  decimal_zero(&example1);
  decimal_zero(&example2);
  s21_from_int_to_decimal(500, &example1);
  s21_from_int_to_decimal(413, &example2);

  // example.bits[0] = 10;
  // example.bits[1] = 10;
  // example.bits[2] = 10;
  // example.bits[3] = 23;
  // printf("%x\n", 0b00000000111111110000000000000000);

  set_scale(&example1, 9);
  set_scale(&example2, 0);

  ///////////
  // big_dec big_example1 = from_decimal_to_big_decimal(example1);
  // big_dec big_example2 = from_decimal_to_big_decimal(example2);
  int error = s21_add(example1, example2, &result);
  if (!error)
    print_dec(result);
  else
    printf("Error: %d!\n", error);
  // printf("%d\n", (int)(413 + 0.000000500));
  return 0;
}

void print_dec(s21_decimal dec) {
  printf("========== D E C I M A L ==========\n");
  if (get_sign(dec) == 1)
    printf("%c", '-');
  else
    printf("%c", '+');
  printf("%010u,", (unsigned)dec.bits[2]);
  printf("%010u,", (unsigned)dec.bits[1]);
  printf("%010u", (unsigned)dec.bits[0]);
  printf("\n\n============= B I T S =============\n");
  printf(
      "31|30|29|28|27|26|25|24|23|22"
      "|21|20|19|18|17|16|15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|\n");
  printf(
      "------------------------------------------------------------------------"
      "------------------------"
      "\n");

  for (int i = 127; i >= 96; i--) printf("%2d|", get_bit(dec, i));
  printf("\n");
  for (int i = 95; i >= 64; i--) printf("%2d|", get_bit(dec, i));
  printf("\n");
  for (int i = 63; i >= 32; i--) printf("%2d|", get_bit(dec, i));
  printf("\n");
  for (int i = 31; i >= 0; i--) printf("%2d|", get_bit(dec, i));
  printf("\n");

  printf("\nSCALE: %d\n", get_scale(dec));
}

void print_big_dec(big_dec dec) {
  printf("\n\n====== B I G   D E C I M A L ======\n");
  if (big_get_sign(dec) == 1)
    printf("%c", '-');
  else
    printf("%c", '+');
  printf("%010u,", (unsigned)dec.bits[6]);
  printf("%010u,", (unsigned)dec.bits[5]);
  printf("%010u,", (unsigned)dec.bits[4]);
  printf("%010u,", (unsigned)dec.bits[3]);
  printf("%010u,", (unsigned)dec.bits[2]);
  printf("%010u,", (unsigned)dec.bits[1]);
  printf("%010u", (unsigned)dec.bits[0]);
  printf("\n\n============= B I T S =============\n");
  printf(
      "31|30|29|28|27|26|25|24|23|22"
      "|21|20|19|18|17|16|15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|\n");
  printf(
      "------------------------------------------------------------------------"
      "------------------------"
      "\n");

  for (int i = 255; i >= 224; i--) printf("%2d|", big_get_bit(dec, i));
  printf("\n");
  for (int i = 223; i >= 192; i--) printf("%2d|", big_get_bit(dec, i));
  printf("\n");
  for (int i = 191; i >= 160; i--) printf("%2d|", big_get_bit(dec, i));
  printf("\n");
  for (int i = 159; i >= 128; i--) printf("%2d|", big_get_bit(dec, i));
  printf("\n");
  for (int i = 127; i >= 96; i--) printf("%2d|", big_get_bit(dec, i));
  printf("\n");
  for (int i = 95; i >= 64; i--) printf("%2d|", big_get_bit(dec, i));
  printf("\n");
  for (int i = 63; i >= 32; i--) printf("%2d|", big_get_bit(dec, i));
  printf("\n");
  for (int i = 31; i >= 0; i--) printf("%2d|", big_get_bit(dec, i));
  printf("\n");

  printf("\nSCALE: %d\n", big_get_scale(dec));
}
