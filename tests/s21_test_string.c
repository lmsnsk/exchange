#include <check.h>
#include <string.h>

#include "../func/s21_string.h"

// MEMCHR TEST
START_TEST(s21_test_memchr_check_1) {
  const char *str = "Hello, how are you?";
  ck_assert_ptr_eq(s21_memchr(str, 'e', 20), memchr(str, 'e', 20));
  ck_assert_ptr_eq(s21_memchr(str, ',', 20), memchr(str, ',', 20));
  ck_assert_ptr_eq(s21_memchr(str, 'a', 2), memchr(str, 'a', 2));
}
END_TEST

Suite *s21_memchr_suit(void) {
  Suite *suite = suite_create("s21_memchr");
  TCase *tcase_memchr_1 = tcase_create("s21_memchr_1");
  TCase *tcase_memchr_2 = tcase_create("s21_memchr_2");
  tcase_add_test(tcase_memchr_1, s21_test_memchr_check_1);
  suite_add_tcase(suite, tcase_memchr_1);
  return suite;
}

int main(void) {
  int failed_count = 0;
  Suite *suite = s21_memchr_suit();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  printf("------------------------------------------\n\n");

  return failed_count != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}