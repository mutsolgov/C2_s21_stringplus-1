#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_strrchr_suite(void);
int s21_strrchr_test(void);

int main(void) {
  int count_failed = s21_strrchr_test();
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

START_TEST(s21_strrchr_test1) {
  char str[] = "Welcome to School 21 Magas!";
  char c = 'a';
  ck_assert(strcmp(s21_strrchr(str, c), strrchr(str, c)) == 0);
}
END_TEST

START_TEST(s21_strrchr_test2) {
  char str[] = "Welcome to School 21 Magas!";
  char c = 'M';
  ck_assert(strcmp(s21_strrchr(str, c), strrchr(str, c)) == 0);
}
END_TEST

START_TEST(s21_strrchr_test3) {
  char str[] = "Welcome to School 21 Magas!";
  char c = '\0';
  ck_assert(strcmp(s21_strrchr(str, c), strrchr(str, c)) == 0);
}
END_TEST

START_TEST(s21_strrchr_test4) {
  char str[] = "";
  char c = 'P';
  ck_assert(s21_strrchr(str, c) == s21_NULL && strrchr(str, c) == s21_NULL);
}
END_TEST

START_TEST(s21_strrchr_test5) {
  char str[] = "Welcome to School 21 Magas!";
  char c = 'N';
  ck_assert(s21_strrchr(str, c) == s21_NULL && strrchr(str, c) == s21_NULL);
}
END_TEST

START_TEST(s21_strrchr_test6) {
  char str[] = "Welcome to School 21 Magas!";
  char c = '!';
  ck_assert(strcmp(s21_strrchr(str, c), strrchr(str, c)) == 0);
}
END_TEST

Suite *s21_strrchr_suite(void) {
  Suite *s;
  s = suite_create("s21_strrchr");
  TCase *tc_strrchr;
  tc_strrchr = tcase_create("strrchr");
  tcase_add_test(tc_strrchr, s21_strrchr_test1);
  tcase_add_test(tc_strrchr, s21_strrchr_test2);
  tcase_add_test(tc_strrchr, s21_strrchr_test3);
  tcase_add_test(tc_strrchr, s21_strrchr_test4);
  tcase_add_test(tc_strrchr, s21_strrchr_test5);
  tcase_add_test(tc_strrchr, s21_strrchr_test6);
  suite_add_tcase(s, tc_strrchr);
  return s;
}

int s21_strrchr_test(void) {
  Suite *s = s21_strrchr_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}