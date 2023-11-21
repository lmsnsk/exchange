#include <check.h>
#include <math.h>

#include "../source/s21_math.h"

START_TEST(s21_test_fmod_check_1) {
  double val1X = -5.495414;
  double val1Y = -5.495414;
  double val2X = 4.957778;
  double val2Y = 4.957778;
  ck_assert_ldouble_eq_tol(s21_fmod(val1X, val1Y), fmod(val1X, val1Y), 1e-06);
  ck_assert_ldouble_eq_tol(s21_fmod(val2X, val2Y), fmod(val2X, val2Y), 1e-06);
}
END_TEST

START_TEST(s21_test_fmod_check_2) {
  double val1X = S21_INF_NEG;
  double val1Y = S21_INF_NEG;
  double val2X = S21_INF_POS;
  double val2Y = S21_INF_POS;
  double val3X = S21_NAN;
  double val3Y = S21_NAN;
  ck_assert_double_infinite(s21_fmod(val1X, val1Y));
  ck_assert_double_infinite(s21_fmod(val2X, val2Y));
  ck_assert_double_nan(s21_fmod(val3X, val3Y));
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