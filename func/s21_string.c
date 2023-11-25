#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int main() {
//   char *str1 = "Hell";
//   // char *str2 = "ll";
//   int a = memcmp(str1, "Hello", 8);
//   printf("%d\n", a);
//   return 0;
// }

void *s21_memchr(const void *str, int c, size_t n) {
  unsigned char *tmp = (unsigned char *)str;
  unsigned char sym = (unsigned char)c;
  void *res = NULL;
  for (size_t i = 0; i < n; i++) {
    if (sym == *tmp) {
      res = tmp;
      break;
    }
    tmp++;
  }
  return res;
}

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  unsigned char *tmp1 = (unsigned char *)str1;
  unsigned char *tmp2 = (unsigned char *)str2;
  for (size_t i = 0; i < n; i++) {
    if (*tmp2 != *tmp1) break;
    tmp1++, tmp2++;
  }
  return *tmp1 - *tmp2;
}

///////////////////////////////////////

size_t s21_strlen(const char *str) {
  size_t length = 0;
  for (; *(str + length); length++)
    ;
  return length;
}

int s21_strcmp(char *str1, char *str2) {
  for (; *str1 && *str1 == *str2; str1++, str2++)
    ;
  return *str1 - *str2;
}

char *s21_strcpy(char *str1, const char *str2) {
  if (str1 == NULL) return NULL;
  char *ptr = str1;
  while (*str2 != '\0') {
    *str1 = *str2;
    str1++;
    str2++;
  }
  *str1 = '\0';
  return ptr;
}

char *s21_strcat(char *str1, const char *str2) {
  char *ptr = str1 + s21_strlen(str1);

  while (*str2 != '\0') {
    *ptr++ = *str2++;
  }
  *ptr = '\0';
  return str1;
}

char *s21_strchr(const char *str, int c) {
  int i = 0;
  while (str[i] && str[i] != c) ++i;
  return c == str[i] ? (char *)str + i : NULL;
}

char *s21_strstr(char *str1, char *str2) {
  while (*str1 != '\0') {
    if ((*str1 == *str2) && s21_strcmp(str1, str2)) {
      return str1;
    }
    str1++;
  }

  return NULL;
}
