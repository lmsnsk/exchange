#include <check.h>
#include <math.h>

#include "../source/s21_math.h"

START_TEST(s21_test_fmod_check_1) {
  double val1X = 20.0;
  double val1Y = 4.0;
  double val2X = 4.957778;
  double val2Y = 1.957778;
  double val3X = -4.957778;
  double val3Y = 1.957778;
  double val4X = -4.957778;
  double val4Y = -1.957778;
  double val5X = -1.547565e10;
  double val5Y = -1.45564554545454545454;
  ck_assert_ldouble_eq_tol(s21_fmod(val1X, val1Y), fmod(val1X, val1Y), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(val2X, val2Y), fmod(val2X, val2Y), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(val3X, val3Y), fmod(val3X, val3Y), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(val4X, val4Y), fmod(val4X, val4Y), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(val5X, val5Y), fmod(val5X, val5Y), 1e-6);
}
END_TEST

START_TEST(s21_test_fmod_check_2) {
  double val1X = 50.0;
  double val1Y = 0.0;
  double val2X = S21_INF_POS;
  double val2Y = 7.65;
  double val3X = S21_INF_NEG;
  double val3Y = 5.444;
  double val4X = S21_NAN;
  double val4Y = 5.01;
  ck_assert_double_nan(s21_fmod(val1X, val1Y));
  ck_assert_double_infinite(s21_fmod(val2X, val2Y));
  ck_assert_double_infinite(s21_fmod(val3X, val3Y));
  ck_assert_double_nan(s21_fmod(val4X, val4Y));
}
END_TEST

Suite *s21_fmod_suit(void) {
  Suite *suite = suite_create("s21_fmod");

  TCase *tcase_fmod_1 = tcase_create("s21_fmod_1");
  TCase *tcase_fmod_2 = tcase_create("s21_fmod_2");

  tcase_add_test(tcase_fmod_1, s21_test_fmod_check_1);
  tcase_add_test(tcase_fmod_2, s21_test_fmod_check_2);

  suite_add_tcase(suite, tcase_fmod_1);
  suite_add_tcase(suite, tcase_fmod_2);

  return suite;
}

int main(void) {
  int failed_count = 0;
  Suite *suite = s21_fmod_suit();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  printf("------------------------------------------\n\n");

  return failed_count != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}