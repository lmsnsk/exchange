#include <limits.h>

#include "s21_decimal.h"

// int main() {
//   s21_decimal example;
//   s21_decimal result;
//   null_decimal(&example);

//   example.bits[0] = 123456;
//   example.bits[1] = 0;
//   example.bits[2] = 0;

//   set_scale(&example, 1);
//   // invert_sign(&example);

//   int error = s21_truncate(example, &result);
//   if (!error) {
//     print_dec(result);
//     printf("OK!\n");
//   } else {
//     printf("Error: %d!\n", error);
//   }

//   // s21_decimal src1, origin;  /// for truncate

//   // src1.bits[0] = 0b10000010111000100101101011101101;
//   // src1.bits[1] = 0b11111001111010000010010110101101;
//   // src1.bits[2] = 0b10110000001111101111000010010100;
//   // src1.bits[3] = 0b10000000000011100000000000000000;
//   // s21_decimal result = {{0, 0, 0, 0}};
//   // s21_truncate(src1, &result);

//   // origin.bits[0] = 0b10000110011101001011101110010001;
//   // origin.bits[1] = 0b00000000000000011111000000010110;
//   // origin.bits[2] = 0b00000000000000000000000000000000;
//   // origin.bits[3] = 0b10000000000000000000000000000000;
//   // print_dec(src1);
//   // print_dec(origin);
//   return 0;
// }

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
