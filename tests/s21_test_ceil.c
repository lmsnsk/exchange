#include <check.h>
#include <math.h>

#include "../source/s21_math.h"

START_TEST(s21_test_ceil_check_1) {
  double val1 = -5.495414;
  double val2 = 4.957778;
  ck_assert_ldouble_eq_tol(s21_ceil(val1), ceil(val1), 1e-06);
  ck_assert_ldouble_eq_tol(s21_ceil(val2), ceil(val2), 1e-06);
}
END_TEST

START_TEST(s21_test_ceil_check_2) {
  for (double i = -1.01; i <= 1.01; i += 0.01) {
    ck_assert_ldouble_eq_tol(s21_ceil(i), ceil(i), 1e-06);
  }
}
END_TEST

START_TEST(s21_test_ceil_check_3) {
  double val1 = S21_INF_NEG;
  double val2 = S21_INF_POS;
  double val3 = S21_NAN;
  ck_assert_double_infinite(s21_ceil(val1));
  ck_assert_double_infinite(s21_ceil(val2));
  ck_assert_double_nan(s21_ceil(val3));
}
END_TEST

Suite *s21_ceil_suit(void) {
  Suite *suite = suite_create("s21_ceil");

  TCase *tcase_ceil_1 = tcase_create("s21_ceil_1");
  TCase *tcase_ceil_2 = tcase_create("s21_ceil_2");
  TCase *tcase_ceil_3 = tcase_create("s21_ceil_3");

  tcase_add_test(tcase_ceil_1, s21_test_ceil_check_1);
  tcase_add_test(tcase_ceil_2, s21_test_ceil_check_2);
  tcase_add_test(tcase_ceil_3, s21_test_ceil_check_3);

  suite_add_tcase(suite, tcase_ceil_1);
  suite_add_tcase(suite, tcase_ceil_2);
  suite_add_tcase(suite, tcase_ceil_3);

  return suite;
}

int main(void) {
  int failed_count = 0;
  Suite *suite = s21_ceil_suit();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  printf("------------------------------------------\n\n");

  return failed_count != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}