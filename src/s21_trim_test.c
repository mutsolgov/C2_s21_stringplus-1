#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_trim_suite(void);
int s21_trim_test(void);

int main(void) {
  int count_failed = s21_trim_test();
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

START_TEST(s21_trim_test1) {
  const char str1[] = "Welcome to School 21 Magas! \n \n   ";
  const char str2[] = " \n";
  const char ref[] = "Welcome to School 21 Magas!";
  char *res;
  ck_assert(strcmp(res = s21_trim(str1, str2), ref) == 0);
  free(res);
}
END_TEST

START_TEST(s21_trim_test2) {
  const char str1[] = "@$ #$ & $ Welcome to School 21 Magas!#& #$ #@#  ";
  const char str2[] = " @#$&";
  const char ref[] = "Welcome to School 21 Magas!";
  char *res;
  ck_assert(strcmp(res = s21_trim(str1, str2), ref) == 0);
  free(res);
}
END_TEST

START_TEST(s21_trim_test3) {
  const char str1[] = "{\t Welcome to School 21 Magas!  \n }";
  const char str2[] = "";
  const char ref[] = "{\t Welcome to School 21 Magas!  \n }";
  char *res;
  ck_assert(strcmp(res = s21_trim(str1, str2), ref) == 0);
  free(res);
}
END_TEST

START_TEST(s21_trim_test4) {
  const char str1[] = "Welcome to School 21 Magas!";
  const char str2[] = " 21 Magas!";
  const char ref[] = "Welcome to School";
  char *res;
  ck_assert(strcmp(res = s21_trim(str1, str2), ref) == 0);
  free(res);
}
END_TEST

START_TEST(s21_trim_test5) {
  const char str1[] = "Welcome to School 21 Magas!";
  const char str2[] = "Welcome ";
  const char ref[] = "to School 21 Magas!";
  char *res;
  ck_assert(strcmp(res = s21_trim(str1, str2), ref) == 0);
  free(res);
}
END_TEST

START_TEST(s21_trim_test6) {
  const char str1[] = " \t \t Welcome to School 21 Magas!";
  const char str2[] = " \t \t Welcome ";
  const char ref[] = "to School 21 Magas!";
  char *res;
  ck_assert(strcmp(res = s21_trim(str1, str2), ref) == 0);
  free(res);
}
END_TEST

Suite *s21_trim_suite(void) {
  Suite *s;
  s = suite_create("s21_trim");
  TCase *tc_trim;
  tc_trim = tcase_create("trim");
  tcase_add_test(tc_trim, s21_trim_test1);
  tcase_add_test(tc_trim, s21_trim_test2);
  tcase_add_test(tc_trim, s21_trim_test3);
  tcase_add_test(tc_trim, s21_trim_test4);
  tcase_add_test(tc_trim, s21_trim_test5);
  tcase_add_test(tc_trim, s21_trim_test6);
  suite_add_tcase(s, tc_trim);
  return s;
}

int s21_trim_test(void) {
  Suite *s = s21_trim_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}