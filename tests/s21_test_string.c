#include <check.h>
#include <string.h>

#include "../func/s21_string.h"

// MEMCHR TEST
START_TEST(s21_test_memchr_check) {
  const char *str = "Hello, how are you?";

  ck_assert_ptr_eq(s21_memchr(str, 'e', 20), memchr(str, 'e', 20));
  ck_assert_ptr_eq(s21_memchr(str, ',', 20), memchr(str, ',', 20));
  ck_assert_ptr_eq(s21_memchr(str, 'a', 2), memchr(str, 'a', 2));
}
END_TEST

Suite *s21_memchr_suit(void) {
  Suite *suite = suite_create("s21_memchr");
  TCase *tcase_memchr = tcase_create("s21_memchr");
  tcase_add_test(tcase_memchr, s21_test_memchr_check);
  suite_add_tcase(suite, tcase_memchr);
  return suite;
}

// MEMCMP TEST
START_TEST(s21_test_memcmp_check) {
  const char *str1 = "Hello, how are you?";
  const char *str2 = "Hello, how are you?";
  const char *str3 = "Hello, Fow are you?";

  ck_assert_int_eq(s21_memcmp(str1, str2, 20), memcmp(str1, str2, 20));
  ck_assert_int_eq(s21_memcmp(str1, str2, 20), memcmp(str1, str2, 20));
  ck_assert_int_eq(s21_memcmp(str1, str2, 2), memcmp(str1, str2, 2));
  ck_assert_int_eq(s21_memcmp(str1, str3, 2), memcmp(str1, str3, 2));
  ck_assert_int_eq(s21_memcmp(str1, str3, 20), memcmp(str1, str3, 20));
  ck_assert_int_eq(s21_memcmp(str3, str2, 20), memcmp(str3, str2, 20));
}
END_TEST

Suite *s21_memcmp_suit(void) {
  Suite *suite = suite_create("s21_memcmp");
  TCase *tcase_string = tcase_create("s21_string_1");
  tcase_add_test(tcase_string, s21_test_memcmp_check);
  suite_add_tcase(suite, tcase_string);
  return suite;
}

// MEMCPY TEST
START_TEST(s21_test_memcpy_check) {
  char dest[100];
  const char *str2 = "wetwetr";
  const char *str3 = "Hello, How are you?ewfweertwtr";
  ck_assert_ptr_eq(s21_memcpy(dest, str2, 20), memcpy(dest, str2, 20));
  ck_assert_ptr_eq(s21_memcpy(dest, str2, 4), memcpy(dest, str2, 4));
  ck_assert_ptr_eq(s21_memcpy(dest, str3, 2), memcpy(dest, str3, 2));
  ck_assert_ptr_eq(s21_memcpy(dest, str3, 33), memcpy(dest, str3, 33));

  ck_assert_str_eq(s21_memcpy(dest, str2, 12), memcpy(dest, str2, 12));
  ck_assert_str_eq(s21_memcpy(dest, str2, 3), memcpy(dest, str2, 3));
  ck_assert_str_eq(s21_memcpy(dest, str3, 2), memcpy(dest, str3, 2));
  ck_assert_str_eq(s21_memcpy(dest, str3, 8), memcpy(dest, str3, 8));
}
END_TEST

Suite *s21_memcpy_suit(void) {
  Suite *suite = suite_create("s21_memcpy");
  TCase *tcase_string = tcase_create("s21_string_1");
  tcase_add_test(tcase_string, s21_test_memcpy_check);
  suite_add_tcase(suite, tcase_string);
  return suite;
}

// MEMSET TEST
START_TEST(s21_test_memset_check) {
  char str[100] = "Hello, how are you?";

  ck_assert_ptr_eq(s21_memset(str, 'e', 7), memset(str, 'e', 7));
  ck_assert_ptr_eq(s21_memset(str, ',', 14), memset(str, ',', 14));
  ck_assert_ptr_eq(s21_memset(str, 'a', 0), memset(str, 'a', 0));

  ck_assert_str_eq(s21_memset(str, 'e', 7), memset(str, 'e', 7));
  ck_assert_str_eq(s21_memset(str, ',', 14), memset(str, ',', 14));
  ck_assert_str_eq(s21_memset(str, 'a', 0), memset(str, 'a', 0));
}
END_TEST

Suite *s21_memset_suit(void) {
  Suite *suite = suite_create("s21_memset");
  TCase *tcase_memset = tcase_create("s21_memset");
  tcase_add_test(tcase_memset, s21_test_memset_check);
  suite_add_tcase(suite, tcase_memset);
  return suite;
}

// STRCAT TEST
START_TEST(s21_test_strcat_check) {
  char str1[100] = "Hello, how are you?";
  char str2[15] = "I am ok!";

  ck_assert_str_eq(s21_strcat(str1, str2), strcat(str1, str2));
  ck_assert_str_eq(s21_strcat(str1, str2), strcat(str1, str2));
  ck_assert_str_eq(s21_strcat(str1, str2), strcat(str1, str2));
}
END_TEST

Suite *s21_strcat_suit(void) {
  Suite *suite = suite_create("s21_strcat");
  TCase *tcase_strcat = tcase_create("s21_strcat");
  tcase_add_test(tcase_strcat, s21_test_strcat_check);
  suite_add_tcase(suite, tcase_strcat);
  return suite;
}

// MAIN PART
int string_srunner(Suite *suite) {
  int failed_count = 0;
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  printf("------------------------------------------\n\n");
  return failed_count;
}

int main(void) {
  int failed_count = 0;
  Suite *suite_memchr = s21_memchr_suit();
  Suite *suite_memcmp = s21_memcmp_suit();
  Suite *suite_memcpy = s21_memcpy_suit();
  Suite *suite_memset = s21_memset_suit();
  Suite *suite_strcat = s21_strcat_suit();
  int failed_memchr = string_srunner(suite_memchr);
  int failed_memcmp = string_srunner(suite_memcmp);
  int failed_memcpy = string_srunner(suite_memcpy);
  int failed_memset = string_srunner(suite_memset);
  int failed_strcat = string_srunner(suite_strcat);

  if (failed_memchr || failed_memcmp || failed_memcpy || failed_memset ||
      failed_strcat)
    failed_count = 1;

  return failed_count != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}