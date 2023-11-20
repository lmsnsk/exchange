#include <check.h>
#include <math.h>

#include "../source/s21_math.h"

START_TEST(s21_test_fabs_check_1) {
  ck_assert_int_eq(s21_fabs(-5.4548454), fabs(-5.4548454));
}
END_TEST

START_TEST(s21_test_fabs_check_2) {
  ck_assert_int_eq(s21_fabs(5.4548454), fabs(5.4548454));
}
END_TEST

START_TEST(s21_test_fabs_check_3) { ck_assert_int_eq(s21_fabs(0), fabs(0)); }
END_TEST

Suite *s21_fabs_suit(void) {
  Suite *suite = suite_create("s21_fabs");

  TCase *tcase_fabs_1 = tcase_create("s21_fabs_1");
  TCase *tcase_fabs_2 = tcase_create("s21_fabs_2");
  TCase *tcase_fabs_3 = tcase_create("s21_fabs_3");

  tcase_add_test(tcase_fabs_1, s21_test_fabs_check_1);
  tcase_add_test(tcase_fabs_2, s21_test_fabs_check_2);
  tcase_add_test(tcase_fabs_3, s21_test_fabs_check_3);

  suite_add_tcase(suite, tcase_fabs_1);
  suite_add_tcase(suite, tcase_fabs_2);
  suite_add_tcase(suite, tcase_fabs_3);
  return suite;
}

int main(void) {
  int failed_count = 0;
  Suite *suite = s21_fabs_suit();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return failed_count != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}