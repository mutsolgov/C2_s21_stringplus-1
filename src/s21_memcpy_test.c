#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_memcpy_suite(void);
int s21_memcpy_test(void);

int main(void) {
  int count_failed = s21_memcpy_test();
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

START_TEST(s21_memcpy_test1) {
  char str1[] = "abcdef";
  char str2[] = "abcdef";
  const char str[] = "ghijkl";
  ck_assert(strcmp(s21_memcpy(str1, str, 5), memcpy(str2, str, 5)) == 0);
}
END_TEST

START_TEST(s21_memcpy_test2) {
  char str1[] = "aBcdef";
  char str2[] = "abCdef";
  const char str[] = "ghijkl";
  ck_assert(strcmp(s21_memcpy(str1, str, 4), memcpy(str2, str, 4)) == 0);
}
END_TEST

START_TEST(s21_memcpy_test3) {
  char str1[] = "abcdef";
  char str2[] = "abcdef";
  const char str[] = "ghijkl";
  ck_assert(strcmp(s21_memcpy(str1, str, 8), memcpy(str2, str, 8)) == 0);
}
END_TEST

START_TEST(s21_memcpy_test4) {
  char str1[] = "aaabbb";
  const char *str2 = str1 + 3;
  char str3[] = "aaabbb";
  char *str4 = str3 + 3;
  ck_assert(strcmp(s21_memcpy(str1, str2, 3), memcpy(str3, str4, 3)) == 0);
}
END_TEST

Suite *s21_memcpy_suite(void) {
  Suite *s;
  s = suite_create("s21_memcpy");
  TCase *tc_memcpy;
  tc_memcpy = tcase_create("memcpy");
  tcase_add_test(tc_memcpy, s21_memcpy_test1);
  tcase_add_test(tc_memcpy, s21_memcpy_test2);
  tcase_add_test(tc_memcpy, s21_memcpy_test3);
  tcase_add_test(tc_memcpy, s21_memcpy_test4);
  suite_add_tcase(s, tc_memcpy);
  return s;
}

int s21_memcpy_test(void) {
  Suite *s = s21_memcpy_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}