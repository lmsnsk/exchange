#include <check.h>
#include <math.h>

#include "../source/s21_math.h"

START_TEST(s21_test_floor_check_1) {
  ck_assert_ldouble_eq_tol(s21_floor(-5.45), floor(-5.45), 1e-6L);
}
END_TEST

START_TEST(s21_test_floor_check_2) {
  ck_assert_ldouble_eq_tol(s21_floor(5.45), floor(5.45), 1e-6L);
}
END_TEST

// START_TEST(s21_test_floor_check_3) {
//   ck_assert_ldouble_eq_tol(s21_floor(S21_NAN), floor(NAN), 1e-6L);
// }
// END_TEST

// START_TEST(s21_test_floor_check_4) {
//   ck_assert_ldouble_eq_tol(s21_floor(S21_INF_NEG), floor(-INFINITY), 1e-6L);
// }
// END_TEST

// START_TEST(s21_test_floor_check_5) {
//   ck_assert_ldouble_eq_tol(s21_floor(S21_INF_POS), floor(INFINITY), 1e-6L);
// }
// END_TEST

Suite *s21_floor_suit(void) {
  Suite *suite = suite_create("s21_floor");

  TCase *tcase_floor_1 = tcase_create("s21_floor_1");
  TCase *tcase_floor_2 = tcase_create("s21_floor_2");
  // TCase *tcase_floor_3 = tcase_create("s21_floor_3");
  // TCase *tcase_floor_4 = tcase_create("s21_floor_4");
  // TCase *tcase_floor_5 = tcase_create("s21_floor_5");

  tcase_add_test(tcase_floor_1, s21_test_floor_check_1);
  tcase_add_test(tcase_floor_2, s21_test_floor_check_2);
  // tcase_add_test(tcase_floor_3, s21_test_floor_check_3);
  // tcase_add_test(tcase_floor_4, s21_test_floor_check_4);
  // tcase_add_test(tcase_floor_5, s21_test_floor_check_5);

  suite_add_tcase(suite, tcase_floor_1);
  suite_add_tcase(suite, tcase_floor_2);
  // suite_add_tcase(suite, tcase_floor_3);
  // suite_add_tcase(suite, tcase_floor_4);
  // suite_add_tcase(suite, tcase_floor_5);

  return suite;
}

int main(void) {
  int failed_count = 0;
  Suite *suite = s21_floor_suit();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  // if (failed_count != 0) printf("\n---\n");

  return failed_count != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}