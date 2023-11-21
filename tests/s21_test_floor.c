#include <check.h>
#include <math.h>

#include "../source/s21_math.h"

START_TEST(s21_test_floor_check_1) {
  double val1 = -5.495414;
  double val2 = 4.957778;
  ck_assert_ldouble_eq_tol(s21_floor(val1), floor(val1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_floor(val2), floor(val2), 1e-6);
}
END_TEST

START_TEST(s21_test_floor_check_2) {
  for (double i = -1.01; i <= 1.01; i += 0.01) {
    ck_assert_ldouble_eq_tol(s21_floor(i), floor(i), 1e-6);
  }
}
END_TEST

START_TEST(s21_test_floor_check_3) {
  double val1 = S21_INF_NEG;
  double val2 = S21_INF_POS;
  double val3 = S21_NAN;
  ck_assert_double_infinite(s21_floor(val1));
  ck_assert_double_infinite(s21_floor(val2));
  ck_assert_double_nan(s21_floor(val3));
}
END_TEST

Suite *s21_floor_suit(void) {
  Suite *suite = suite_create("s21_floor");

  TCase *tcase_floor_1 = tcase_create("s21_floor_1");
  TCase *tcase_floor_2 = tcase_create("s21_floor_2");
  TCase *tcase_floor_3 = tcase_create("s21_floor_3");

  tcase_add_test(tcase_floor_1, s21_test_floor_check_1);
  tcase_add_test(tcase_floor_2, s21_test_floor_check_2);
  tcase_add_test(tcase_floor_3, s21_test_floor_check_3);

  suite_add_tcase(suite, tcase_floor_1);
  suite_add_tcase(suite, tcase_floor_2);
  suite_add_tcase(suite, tcase_floor_3);

  return suite;
}

int main(void) {
  int failed_count = 0;
  Suite *suite = s21_floor_suit();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  printf("------------------------------------------\n\n");

  return failed_count != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}