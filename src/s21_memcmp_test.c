#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_memcmp_suite(void);
int s21_memcmp_test(void);

int main(void) {
  int count_failed = s21_memcmp_test();
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

START_TEST(s21_memcmp_test1) {
  char str1[] = "abcDefg";
  char str2[] = "abcdefg";
  ck_assert(s21_memcmp(str1, str2, 5) == memcmp(str1, str2, 7));
}
END_TEST

START_TEST(s21_memcmp_test2) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  char str2[] = "abcdefghijklmnopqrstuvwxyz";
  ck_assert(s21_memcmp(str1, str2, 9) == memcmp(str1, str2, 20));
}
END_TEST

START_TEST(s21_memcmp_test3) {
  char str1[] = "docker";
  char str2[] = "linux";
  ck_assert(s21_memcmp(str1, str2, 5) == memcmp(str1, str2, 5));
}
END_TEST

START_TEST(s21_memcmp_test4) {
  char str1[] = "ABCDEFG";
  char str2[] = "abcdefg";
  ck_assert(s21_memcmp(str1, str2, 7) == memcmp(str1, str2, 7));
}
END_TEST

Suite *s21_memcmp_suite(void) {
  Suite *s;
  s = suite_create("s21_memcmp");
  TCase *tc_memcmp;
  tc_memcmp = tcase_create("memcmp");
  tcase_add_test(tc_memcmp, s21_memcmp_test1);
  tcase_add_test(tc_memcmp, s21_memcmp_test2);
  tcase_add_test(tc_memcmp, s21_memcmp_test3);
  tcase_add_test(tc_memcmp, s21_memcmp_test4);
  suite_add_tcase(s, tc_memcmp);
  return s;
}

int s21_memcmp_test(void) {
  Suite *s = s21_memcmp_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}