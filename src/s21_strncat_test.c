#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_strncat_suite(void);
int s21_strncat_test(void);

int main(void) {
  int count_failed = s21_strncat_test();
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

START_TEST(s21_strncat_test1) {
  char str1[15] = "abcdef";
  char str2[15] = "abcdef";
  const char str[] = "ghijklmn";
  ck_assert(strcmp(s21_strncat(str1, str, 8), strncat(str2, str, 8)) == 0);
}
END_TEST

START_TEST(s21_strncat_test2) {
  char str1[9] = "01234";
  char str2[9] = "01234";
  const char str[] = "abcdef";
  ck_assert(strcmp(s21_strncat(str1, str, 3), strncat(str2, str, 3)) == 0);
}
END_TEST

START_TEST(s21_strncat_test3) {
  char str1[] = "abcdef";
  char str2[] = "abcdef";
  const char str[] = "0123456789";
  ck_assert(strcmp(s21_strncat(str1, str, 0), strncat(str2, str, 0)) == 0);
}
END_TEST

START_TEST(s21_strncat_test4) {
  char str1[19] = "abcdef";
  char str2[19] = "abcdef";
  const char str[] = "0123456789";
  ck_assert(strcmp(s21_strncat(str1, str, 12), strncat(str2, str, 12)) == 0);
}
END_TEST

Suite *s21_strncat_suite(void) {
  Suite *s = suite_create("s21_strncat");
  TCase *tc_strncat = tcase_create("strncat");
  tcase_add_test(tc_strncat, s21_strncat_test1);
  tcase_add_test(tc_strncat, s21_strncat_test2);
  tcase_add_test(tc_strncat, s21_strncat_test3);
  tcase_add_test(tc_strncat, s21_strncat_test4);
  suite_add_tcase(s, tc_strncat);
  return s;
}

int s21_strncat_test(void) {
  Suite *s = s21_strncat_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}