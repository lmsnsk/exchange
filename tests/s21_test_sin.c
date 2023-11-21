#include <check.h>
#include <math.h>

#include "../source/s21_math.h"

START_TEST(s21_test_sin_check_1) {
  double val1 = 0.000001;
  double val2 = 0;
  double val3 = -4e7;
  double val4 = 19587;
  ck_assert_ldouble_eq_tol(s21_sin(val1), sin(val1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(val2), sin(val2), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(val3), sin(val3), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(val4), sin(val4), 1e-6);
}
END_TEST

START_TEST(s21_test_sin_check_2) {
  for (double i = -S21_PI * 5; i <= S21_PI * 5; i += 0.1) {
    ck_assert_ldouble_eq_tol(s21_sin(i), sin(i), 1e-6);
  }
}
END_TEST

START_TEST(s21_test_sin_check_3) {
  double val1 = S21_INF_NEG;
  double val2 = S21_INF_POS;
  double val3 = S21_NAN;
  ck_assert_double_nan(s21_sin(val1));
  ck_assert_double_nan(s21_sin(val2));
  ck_assert_double_nan(s21_sin(val3));
}
END_TEST

Suite *s21_sin_suit(void) {
  Suite *suite = suite_create("s21_sin");

  TCase *tcase_sin_1 = tcase_create("s21_sin_1");
  TCase *tcase_sin_2 = tcase_create("s21_sin_2");
  TCase *tcase_sin_3 = tcase_create("s21_sin_3");

  tcase_add_test(tcase_sin_1, s21_test_sin_check_1);
  tcase_add_test(tcase_sin_2, s21_test_sin_check_2);
  tcase_add_test(tcase_sin_2, s21_test_sin_check_3);

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