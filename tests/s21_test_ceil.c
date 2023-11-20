#include <check.h>
#include <math.h>

#include "../source/s21_math.h"

START_TEST(s21_test_ceil_check_1) {
  ck_assert_ldouble_eq_tol(s21_ceil(-5.45), ceil(-5.45), 1e-6L);
}
END_TEST

START_TEST(s21_test_ceil_check_2) {
  ck_assert_ldouble_eq_tol(s21_ceil(5.45), ceil(5.45), 1e-6L);
}
END_TEST

// START_TEST(s21_test_ceil_check_3) {
//   ck_assert_ldouble_eq_tol(s21_ceil(S21_NAN), ceil(NAN), 1e-6L);
// }
// END_TEST

// START_TEST(s21_test_ceil_check_4) {
//   ck_assert_ldouble_eq_tol(s21_ceil(S21_INF_NEG), ceil(-INFINITY), 1e-6L);
// }
// END_TEST

// START_TEST(s21_test_ceil_check_5) {
//   ck_assert_ldouble_eq_tol(s21_ceil(S21_INF_POS), ceil(INFINITY), 1e-6L);
// }
// END_TEST

Suite *s21_ceil_suit(void) {
  Suite *suite = suite_create("s21_ceil");

  TCase *tcase_ceil_1 = tcase_create("s21_ceil_1");
  TCase *tcase_ceil_2 = tcase_create("s21_ceil_2");
  // TCase *tcase_ceil_3 = tcase_create("s21_ceil_3");
  // TCase *tcase_ceil_4 = tcase_create("s21_ceil_4");
  // TCase *tcase_ceil_5 = tcase_create("s21_ceil_5");

  tcase_add_test(tcase_ceil_1, s21_test_ceil_check_1);
  tcase_add_test(tcase_ceil_2, s21_test_ceil_check_2);
  // tcase_add_test(tcase_ceil_3, s21_test_ceil_check_3);
  // tcase_add_test(tcase_ceil_4, s21_test_ceil_check_4);
  // tcase_add_test(tcase_ceil_5, s21_test_ceil_check_5);

  suite_add_tcase(suite, tcase_ceil_1);
  suite_add_tcase(suite, tcase_ceil_2);
  // suite_add_tcase(suite, tcase_ceil_3);
  // suite_add_tcase(suite, tcase_ceil_4);
  // suite_add_tcase(suite, tcase_ceil_5);

  return suite;
}

int main(void) {
  int failed_count = 0;
  Suite *suite = s21_ceil_suit();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return failed_count != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}