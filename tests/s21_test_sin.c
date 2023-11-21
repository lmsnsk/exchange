#include <check.h>
#include <math.h>

#include "../source/s21_math.h"

START_TEST(s21_test_sin_check_1) {
  ck_assert_ldouble_eq_tol(s21_sin(1), sin(1), 1e-6);
}
END_TEST

START_TEST(s21_test_sin_check_2) {
  ck_assert_ldouble_eq_tol(s21_sin(5.4548454), sin(5.4548454), 1e-6);
}
END_TEST

START_TEST(s21_test_sin_check_3) {
  ck_assert_ldouble_eq_tol(s21_sin(0), sin(0), 1e-6);
}
END_TEST

Suite *s21_sin_suit(void) {
  Suite *suite = suite_create("s21_sin");

  TCase *tcase_sin_1 = tcase_create("s21_sin_1");
  TCase *tcase_sin_2 = tcase_create("s21_sin_2");
  TCase *tcase_sin_3 = tcase_create("s21_sin_3");

  tcase_add_test(tcase_sin_1, s21_test_sin_check_1);
  tcase_add_test(tcase_sin_2, s21_test_sin_check_2);
  tcase_add_test(tcase_sin_3, s21_test_sin_check_3);

  suite_add_tcase(suite, tcase_sin_1);
  suite_add_tcase(suite, tcase_sin_2);
  suite_add_tcase(suite, tcase_sin_3);
  return suite;
}

int main(void) {
  int failed_count = 0;
  Suite *suite = s21_sin_suit();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  printf("------------------------------------------\n\n");

  return failed_count != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}