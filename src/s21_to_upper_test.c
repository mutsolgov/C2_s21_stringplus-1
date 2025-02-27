#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_to_upper_suite(void);
int s21_to_upper_test(void);

int main(void) {
  int count_failed = s21_to_upper_test();
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

START_TEST(s21_to_upper_test1) {
  const char str1[] = "Welcome to the School 21 Magas!";
  const char str2[] = "WELCOME TO THE SCHOOL 21 MAGAS!";
  char *res;

  ck_assert(strcmp(res = s21_to_upper(str1), str2) == 0);
  free(res);
}
END_TEST

START_TEST(s21_to_upper_test2) {
  const char str1[] = "This is string.\n";
  const char str2[] = "THIS IS STRING.\n";
  char *res;

  ck_assert(strcmp(res = s21_to_upper(str1), str2) == 0);
  free(res);
}
END_TEST

START_TEST(s21_to_upper_test3) {
  const char str1[] = "";
  const char str2[] = "";
  char *res;
  ck_assert(strcmp(res = s21_to_upper(str1), str2) == 0);
  free(res);
}
END_TEST

Suite *s21_to_upper_suite(void) {
  Suite *s;
  s = suite_create("s21_to_upper");
  TCase *tc_to_upper;
  tc_to_upper = tcase_create("to_upper");
  tcase_add_test(tc_to_upper, s21_to_upper_test1);
  tcase_add_test(tc_to_upper, s21_to_upper_test2);
  tcase_add_test(tc_to_upper, s21_to_upper_test3);
  suite_add_tcase(s, tc_to_upper);
  return s;
}

int s21_to_upper_test(void) {
  Suite *s = s21_to_upper_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}
