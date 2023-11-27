#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char src[100] = "Horosiy denn";
  char str[100] = "zaebis ";
  size_t ind = 13;
  void *tmp = s21_insert(src, str, ind);
  printf("%p\n", tmp);
  if (tmp) free(tmp);
  return 0;
}

void *s21_memchr(const void *str, int c, size_t n) {
  unsigned char *tmp = (unsigned char *)str;
  unsigned char sym = (unsigned char)c;
  void *res = S21_NULL;
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

void *s21_memcpy(void *dest, const void *src, size_t n) {
  char *tmp1 = (char *)dest;
  char *tmp2 = (char *)src;
  for (size_t i = 0; i < n; i++) {
    *tmp1++ = *tmp2++;
  }
  return dest;
}

void *s21_memset(void *str, int c, size_t n) {
  unsigned char *tmp = (unsigned char *)str;
  for (size_t i = 0; i < n; i++) {
    *tmp++ = (unsigned char)c;
  }
  return str;
}

char *s21_strcat(char *str1, const char *str2) {
  char *ptr = str1 + s21_strlen(str1);
  while (*str2 != '\0') {
    *ptr++ = *str2++;
  }
  *ptr = '\0';
  return str1;
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
  if (str1 == S21_NULL) return S21_NULL;
  char *ptr = str1;
  while (*str2 != '\0') {
    *str1 = *str2;
    str1++;
    str2++;
  }
  *str1 = '\0';
  return ptr;
}

char *s21_strchr(const char *str, int c) {
  int i = 0;
  while (str[i] && str[i] != c) ++i;
  return c == str[i] ? (char *)str + i : S21_NULL;
}

char *s21_strstr(char *str1, char *str2) {
  while (*str1 != '\0') {
    if ((*str1 == *str2) && s21_strcmp(str1, str2)) {
      return str1;
    }
    str1++;
  }

  return S21_NULL;
}

void *s21_to_lower(const char *str) {
  char *copy_str = S21_NULL;
  if (str) {
    copy_str = malloc(s21_strlen(str) + 2);
    if (copy_str) {
      for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] > 64 && str[i] < 91)
          copy_str[i] = str[i] + 32;
        else
          copy_str[i] = str[i];
      }
    }
  }
  return (void *)copy_str;
}

void *s21_to_upper(const char *str) {
  char *copy_str = S21_NULL;
  if (str) {
    copy_str = malloc(s21_strlen(str) + 2);
    if (copy_str) {
      for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] > 96 && str[i] < 123)
          copy_str[i] = str[i] - 32;
        else
          copy_str[i] = str[i];
      }
    }
  }
  return (void *)copy_str;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
  char *new_string = S21_NULL;
  size_t l1 = s21_strlen(src);
  if (src && str && start_index <= l1) {
    size_t l2 = s21_strlen(str);
    new_string = calloc(l1 + l2 + 2, 1);
    if (new_string) {
      for (size_t i = 0; i < (l1 + l2); i++) {
        if (i < start_index) {
          new_string[i] = src[i];
        } else if (i >= start_index && i < l2 + start_index) {
          new_string[i] = str[i - start_index];
        } else {
          new_string[i] = src[i - l2];
        }
      }
    }
  }
  return (void *)new_string;
}
