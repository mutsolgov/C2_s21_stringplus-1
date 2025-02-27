#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_strerror_suite(void);
int s21_strerror_test(void);

int main(void) {
  int count_failed = s21_strerror_test();
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

START_TEST(s21_strerror_test1) {
  int errnum = 0;
  char *s21_res = s21_strerror(errnum);
  char *res = strerror(errnum);
  ck_assert(strcmp(s21_res, res) == 0);
}
END_TEST

START_TEST(s21_strerror_test2) {
  int errnum = 40;
  char *s21_res = s21_strerror(errnum);
  char *res = strerror(errnum);
  ck_assert(strcmp(s21_res, res) == 0);
}
END_TEST

START_TEST(s21_strerror_test3) {
  int errnum = 80;
  char *s21_res = s21_strerror(errnum);
  char *res = strerror(errnum);
  ck_assert(strcmp(s21_res, res) == 0);
}
END_TEST

START_TEST(s21_strerror_test4) {
  int errnum = 100;
  char *s21_res = s21_strerror(errnum);
  char *res = strerror(errnum);
  ck_assert(strcmp(s21_res, res) == 0);
}
END_TEST

START_TEST(s21_strerror_test5) {
  int errnum = -1;
  char *s21_res = s21_strerror(errnum);
  char *res = strerror(errnum);
  ck_assert(strcmp(s21_res, res) == 0);
}
END_TEST

START_TEST(s21_strerror_test6) {
  int errnum = 1215752191;
  char *s21_res = s21_strerror(errnum);
  char *res = strerror(errnum);
  ck_assert(strcmp(s21_res, res) == 0);
}
END_TEST

Suite *s21_strerror_suite(void) {
  Suite *s;
  s = suite_create("s21_strerror");
  TCase *tc_strerror;
  tc_strerror = tcase_create("strerror");
  tcase_add_test(tc_strerror, s21_strerror_test1);
  tcase_add_test(tc_strerror, s21_strerror_test2);
  tcase_add_test(tc_strerror, s21_strerror_test3);
  tcase_add_test(tc_strerror, s21_strerror_test4);
  tcase_add_test(tc_strerror, s21_strerror_test5);
  tcase_add_test(tc_strerror, s21_strerror_test6);
  suite_add_tcase(s, tc_strerror);
  return s;
}

int s21_strerror_test(void) {
  Suite *s = s21_strerror_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}