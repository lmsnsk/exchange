#ifndef S21_STRING
#define S21_STRING
#include <stdlib.h>

size_t s21_strlen(const char* str);
int s21_strcmp(char* str1, char* str2);
char* s21_strcpy(char* str1, const char* str2);
char* s21_strcat(char* str1, const char* str2);
char* s21_strchr(const char* str, int c);
char* s21_strstr(char* str1, char* str2);

void* s21_memchr(const void* str, int c, size_t n);
int s21_memcmp(const void* str1, const void* str2, size_t n);

#endif
