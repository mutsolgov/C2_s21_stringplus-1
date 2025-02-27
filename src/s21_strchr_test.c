#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_strchr_suite(void);
int s21_strchr_test(void);

int main(void) {
  int count_failed = s21_strchr_test();
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

START_TEST(s21_strchr_test1) {
  char str[] = "Welcome to School 21 Magas!";
  char c = 'W';
  ck_assert(strcmp(s21_strchr(str, c), strchr(str, c)) == 0);
}
END_TEST

START_TEST(s21_strchr_test2) {
  char str[] = "Welcome to School 21 Magas!";
  char c = '!';
  ck_assert(strcmp(s21_strchr(str, c), strchr(str, c)) == 0);
}
END_TEST

START_TEST(s21_strchr_test3) {
  char str[] = "Welcome to School 21 Magas!";
  char c = 'o';
  ck_assert(strcmp(s21_strchr(str, c), strchr(str, c)) == 0);
}
END_TEST

START_TEST(s21_strchr_test4) {
  char str[] = "Welcome to School 21 Magas!";
  char c = 'N';
  ck_assert(s21_strchr(str, c) == s21_NULL && strchr(str, c) == NULL);
}
END_TEST

START_TEST(s21_strchr_test5) {
  char str[] = "";
  char c = 'S';
  ck_assert(s21_strchr(str, c) == s21_NULL && strchr(str, c) == NULL);
}
END_TEST

START_TEST(s21_strchr_test6) {
  char str[] = "Welcome to School 21 Magas!";
  char c = ' ';
  ck_assert(strcmp(s21_strchr(str, c), strchr(str, c)) == 0);
}
END_TEST

START_TEST(s21_strchr_test7) {
  char str[] = "Welcome to School 21 Magas!";
  char c = '2';
  ck_assert(strcmp(s21_strchr(str, c), strchr(str, c)) == 0);
}
END_TEST

START_TEST(s21_strchr_test8) {
  char str[] = "Welcome to School 21 Magas!";
  char c = '\0';
  ck_assert(strcmp(s21_strchr(str, c), strchr(str, c)) == 0);
}
END_TEST

Suite *s21_strchr_suite(void) {
  Suite *s;
  s = suite_create("s21_strchr");
  TCase *tc_strchr;
  tc_strchr = tcase_create("strchr");
  tcase_add_test(tc_strchr, s21_strchr_test1);
  tcase_add_test(tc_strchr, s21_strchr_test2);
  tcase_add_test(tc_strchr, s21_strchr_test3);
  tcase_add_test(tc_strchr, s21_strchr_test4);
  tcase_add_test(tc_strchr, s21_strchr_test5);
  tcase_add_test(tc_strchr, s21_strchr_test6);
  tcase_add_test(tc_strchr, s21_strchr_test7);
  tcase_add_test(tc_strchr, s21_strchr_test8);
  suite_add_tcase(s, tc_strchr);
  return s;
}

int s21_strchr_test(void) {
  Suite *s = s21_strchr_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}