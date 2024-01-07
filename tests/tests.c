#include "tests.h"

void run_testcase(Suite* testcase) {
  printf("\n");
  SRunner* sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

int main(void) {
  run_testcase(suite_from_int_to_decimal());
  run_testcase(suite_from_decimal_to_float());
  run_testcase(suite_from_decimal_to_int());
  run_testcase(suite_float_to_decimal());
  run_testcase(suite_is_greater());
  run_testcase(suite_is_greater_or_equal());
  run_testcase(suite_is_less());
  run_testcase(suite_is_less_or_equal());
  run_testcase(suite_is_equal());
  run_testcase(suite_is_not_equal());
  run_testcase(suite_truncate());
  run_testcase(suite_floor());
  run_testcase(suite_round());
  run_testcase(suite_negate());
  run_testcase(suite_add());
  run_testcase(suite_sub());
  run_testcase(suite_mul());
  run_testcase(suite_div());

  return 0;
}