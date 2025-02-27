#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_insert_suite(void);
int s21_insert_test(void);

int main(void) {
  int count_failed = s21_insert_test();
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

START_TEST(s21_insert_test1) {
  const char str1[] = "Welcome !";
  const char str2[] = "to School 21";
  const char str[] = "Welcome to School 21!";
  char *res;
  ck_assert(strcmp(res = s21_insert(str1, str2, 8), str) == 0);
  if (res != s21_NULL) free(res);
}
END_TEST

START_TEST(s21_insert_test2) {
  const char str1[] = "This is string!";
  const char str2[] = "";
  const char str[] = "This is string!";
  char *res;
  ck_assert(strcmp(res = s21_insert(str1, str2, 1), str) == 0);
  if (res != s21_NULL) free(res);
}
END_TEST

START_TEST(s21_insert_test3) {
  const char str1[] = "Hello, ";
  const char str2[] = "World!";
  const char str[] = "Hello, World!";
  char *res;
  ck_assert(strcmp(res = s21_insert(str1, str2, 7), str) == 0);
  if (res != s21_NULL) free(res);
}
END_TEST

START_TEST(s21_insert_test4) {
  const char str1[] = "Welcome to School";
  const char str2[] = "!";
  char *res;
  ck_assert((res = s21_insert(str1, str2, 99)) == s21_NULL);
  if (res != s21_NULL) free(res);
}
END_TEST

START_TEST(s21_insert_test5) {
  const char str1[] = "";
  const char str2[] = "This is string!";
  const char str[] = "This is string!";
  char *res;
  ck_assert(strcmp(res = s21_insert(str1, str2, 0), str) == 0);
  if (res != s21_NULL) free(res);
}
END_TEST

Suite *s21_insert_suite(void) {
  Suite *s;
  s = suite_create("s21_insert");
  TCase *tc_insert;
  tc_insert = tcase_create("insert");
  tcase_add_test(tc_insert, s21_insert_test1);
  tcase_add_test(tc_insert, s21_insert_test2);
  tcase_add_test(tc_insert, s21_insert_test3);
  tcase_add_test(tc_insert, s21_insert_test4);
  tcase_add_test(tc_insert, s21_insert_test5);
  suite_add_tcase(s, tc_insert);
  return s;
}

int s21_insert_test(void) {
  Suite *s = s21_insert_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}