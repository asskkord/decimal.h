#include "s21_main_tests.h"

int main() {
  int failed_count = 0;
  Suite *s21_decimal_suite_create[] = {s21_add_suite(),
                                       s21_is_less_suite(),
                                       s21_is_equal_suite(),
                                       s21_is_less_or_equal_suite(),
                                       s21_is_greater_suite(),
                                       s21_is_greater_or_equal_suite(),
                                       s21_is_not_equal_suite(),
                                       s21_mul_suite(),
                                       s21_sub_suite(),
                                       s21_truncate_suite(),
                                       s21_floor_suite(),
                                       s21_from_int_to_decimal_suite(),
                                       suite_from_float_to_decimal(),
                                       s21_negate_suite(),
                                       suite_from_decimal_to_int(),
                                       suite_from_decimal_to_float(),
                                       s21_round_suite(),
                                       s21_random_suite(),
                                       NULL};
  for (int i = 0; s21_decimal_suite_create[i] != NULL; i++) {
    SRunner *suite_runner = srunner_create(s21_decimal_suite_create[i]);

    srunner_set_fork_status(suite_runner, CK_NOFORK);
    srunner_run_all(suite_runner, CK_NORMAL);

    failed_count += srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
  }

  printf("\033[%dm FAILED: %d \033[0m \n", failed_count ? 41 : 42,
         failed_count);

  return (failed_count == 0) ? 0 : 1;
}