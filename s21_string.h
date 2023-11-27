#ifndef S21_STRING
#define S21_STRING
#include <stdio.h>
#include <stdlib.h>

#define S21_NULL (void*)0

size_t s21_strlen(const char* str);
int s21_strcmp(char* str1, char* str2);
char* s21_strcpy(char* str1, const char* str2);
char* s21_strcat(char* str1, const char* str2);
char* s21_strchr(const char* str, int c);
char* s21_strstr(char* str1, char* str2);
void* s21_memchr(const void* str, int c, size_t n);
int s21_memcmp(const void* str1, const void* str2, size_t n);
void* s21_memcpy(void* dest, const void* src, size_t n);
void* s21_memset(void* str, int c, size_t n);
void* s21_to_lower(const char* str);
void* s21_to_upper(const char* str);
void* s21_insert(const char* src, const char* str, size_t start_index);
void* s21_trim(const char* src, const char* trim_chars);
void find_space_limits(const char* src, size_t l1, int* start, int* end);

#endif
