#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_strncmp_suite(void);
int s21_strncmp_test(void);

int main(void) {
  int count_failed = s21_strncmp_test();
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

START_TEST(s21_strncmp_test1) {
  char str1[] = "School 21 Magas";
  char str2[] = "School 21 Magas";
  ck_assert(s21_strncmp(str1, str2, 10) == strncmp(str1, str2, 10));
}
END_TEST

START_TEST(s21_strncmp_test2) {
  char str1[] = "School 21 Magas";
  char str2[] = "School 21";
  ck_assert(s21_strncmp(str1, str2, 9) == strncmp(str1, str2, 9));
}
END_TEST

START_TEST(s21_strncmp_test3) {
  char str1[] = "School 21 Magas";
  char str2[] = "School21 Magas";
  ck_assert(s21_strncmp(str1, str2, 12) == strncmp(str1, str2, 12));
}
END_TEST

START_TEST(s21_strncmp_test4) {
  char str1[] = "School 21 Magas";
  char str2[] = "21 School Magas";
  ck_assert(s21_strncmp(str1, str2, 1) == strncmp(str1, str2, 1));
}
END_TEST

START_TEST(s21_strncmp_test5) {
  char str1[] = "School 21 Magas";
  char str2[] = "";
  ck_assert(s21_strncmp(str1, str2, 5) == strncmp(str1, str2, 5));
}
END_TEST

START_TEST(s21_strncmp_test6) {
  char str1[] = "School 21 Magas";
  char str2[] = "School 21 Magas!";
  ck_assert(s21_strncmp(str1, str2, 0) == strncmp(str1, str2, 0));
}
END_TEST

Suite *s21_strncmp_suite(void) {
  Suite *s;
  s = suite_create("s21_strncmp");
  TCase *tc_strncmp;
  tc_strncmp = tcase_create("strncmp");
  tcase_add_test(tc_strncmp, s21_strncmp_test1);
  tcase_add_test(tc_strncmp, s21_strncmp_test2);
  tcase_add_test(tc_strncmp, s21_strncmp_test3);
  tcase_add_test(tc_strncmp, s21_strncmp_test4);
  tcase_add_test(tc_strncmp, s21_strncmp_test5);
  tcase_add_test(tc_strncmp, s21_strncmp_test6);
  suite_add_tcase(s, tc_strncmp);
  return s;
}

int s21_strncmp_test(void) {
  Suite *s = s21_strncmp_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}