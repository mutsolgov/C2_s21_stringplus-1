#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_strstr_suite(void);
int s21_strstr_test(void);

int main(void) {
  int count_failed = s21_strstr_test();
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

START_TEST(s21_strstr_test1) {
  char str1[] = "Welcome to School 21 Magas";
  char str2[] = "School";
  ck_assert(strcmp(s21_strstr(str1, str2), strstr(str1, str2)) == 0);
}
END_TEST

START_TEST(s21_strstr_test2) {
  char str1[] = "Welcome to School 21 Magas";
  char str2[] = "WeLCom";
  ck_assert(s21_strstr(str1, str2) == s21_NULL &&
            strstr(str1, str2) == s21_NULL);
}
END_TEST

START_TEST(s21_strstr_test3) {
  char str1[] = "Welcome to School 21 Magas";
  char str2[] = "s123";
  ck_assert(s21_strstr(str1, str2) == s21_NULL &&
            strstr(str1, str2) == s21_NULL);
}
END_TEST

START_TEST(s21_strstr_test4) {
  char str1[] = "Welcome to School 21 Magas";
  char str2[] = "Magas";
  ck_assert(strcmp(s21_strstr(str1, str2), strstr(str1, str2)) == 0);
}
END_TEST

START_TEST(s21_strstr_test5) {
  char str1[] = "Welcome to School 21 Magas";
  char str2[] = "Schoagas";
  ck_assert(s21_strstr(str1, str2) == s21_NULL &&
            strstr(str1, str2) == s21_NULL);
}
END_TEST

START_TEST(s21_strstr_test6) {
  char str1[] = "Welcome to School 21 Magas";
  char str2[] = "Test";
  ck_assert(s21_strstr(str1, str2) == s21_NULL &&
            strstr(str1, str2) == s21_NULL);
}
END_TEST

Suite *s21_strstr_suite(void) {
  Suite *s;
  s = suite_create("s21_strstr");
  TCase *tc_strstr;
  tc_strstr = tcase_create("strstr");
  tcase_add_test(tc_strstr, s21_strstr_test1);
  tcase_add_test(tc_strstr, s21_strstr_test2);
  tcase_add_test(tc_strstr, s21_strstr_test3);
  tcase_add_test(tc_strstr, s21_strstr_test4);
  tcase_add_test(tc_strstr, s21_strstr_test5);
  tcase_add_test(tc_strstr, s21_strstr_test6);
  suite_add_tcase(s, tc_strstr);
  return s;
}

int s21_strstr_test(void) {
  Suite *s = s21_strstr_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}