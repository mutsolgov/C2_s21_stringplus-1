#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_memset_suite(void);
int s21_memset_test(void);

int main(void) {
  int count_failed = s21_memset_test();
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

START_TEST(s21_memset_test1) {
  char str1[] = "abcdef";
  char str2[] = "abcdef";
  ck_assert(strcmp(s21_memset(str1, 'Z', 6), memset(str2, 'Z', 6)) == 0);
}
END_TEST

START_TEST(s21_memset_test2) {
  char str1[] = "abcdef";
  char str2[] = "ghijkl";
  ck_assert(strcmp(s21_memset(str1, 111, 6), memset(str2, 111, 6)) == 0);
}
END_TEST

START_TEST(s21_memset_test3) {
  char str1[] = "abcxyz";
  char str2[] = "efgxyz";
  ck_assert(strcmp(s21_memset(str1, 247, 3), memset(str2, 247, 3)) == 0);
}
END_TEST

START_TEST(s21_memset_test4) {
  char str1[] = "abcxabc";
  char str2[] = "efgnabc";
  ck_assert(strcmp(s21_memset(str1, 'n', 4), memset(str2, 'n', 3)) == 0);
}
END_TEST

Suite *s21_memset_suite(void) {
  Suite *s;
  s = suite_create("s21_memset");
  TCase *tc_memset;
  tc_memset = tcase_create("memset");
  tcase_add_test(tc_memset, s21_memset_test1);
  tcase_add_test(tc_memset, s21_memset_test2);
  tcase_add_test(tc_memset, s21_memset_test3);
  tcase_add_test(tc_memset, s21_memset_test4);
  suite_add_tcase(s, tc_memset);
  return s;
}

int s21_memset_test(void) {
  Suite *s = s21_memset_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}