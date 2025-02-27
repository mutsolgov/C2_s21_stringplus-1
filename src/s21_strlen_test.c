#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_strlen_suite(void);
int s21_strlen_test(void);

int main(void) {
  int count_failed = s21_strlen_test();
  if (count_failed > 0) {
    printf("====================\n");
    printf("Tests failed: %d\n", count_failed);
    printf("====================\n");
  } else {
    printf("====================\n");
    printf("Tests success\n");
    printf("====================\n");
  }
  return 0;
}

START_TEST(s21_strlen_test1) {
  char str[] = "Test strlen";
  ck_assert(s21_strlen(str) == strlen(str));
}
END_TEST

START_TEST(s21_strlen_test2) {
  char *str = "      ";
  ck_assert(s21_strlen(str) == strlen(str));
}
END_TEST

START_TEST(s21_strlen_test3) {
  char str[] = "";
  ck_assert(s21_strlen(str) == strlen(str));
}
END_TEST

START_TEST(s21_strlen_test4) {
  char *str = "\0";
  ck_assert(s21_strlen(str) == strlen(str));
}
END_TEST

Suite *s21_strlen_suite(void) {
  Suite *s;
  s = suite_create("s21_strlen");
  TCase *tc_strlen;
  tc_strlen = tcase_create("strlen");
  tcase_add_test(tc_strlen, s21_strlen_test1);
  tcase_add_test(tc_strlen, s21_strlen_test2);
  tcase_add_test(tc_strlen, s21_strlen_test3);
  tcase_add_test(tc_strlen, s21_strlen_test4);
  suite_add_tcase(s, tc_strlen);
  return s;
}

int s21_strlen_test(void) {
  Suite *s = s21_strlen_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}