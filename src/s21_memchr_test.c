#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_memchr_suite(void);
int s21_memchr_test(void);

int main(void) {
  int count_failed = s21_memchr_test();
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

START_TEST(s21_memchr_test1) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  // printf("str1       =  %p\n - %d\n", &str1[13], (int)str1[13]);
  // printf("s21_memchr =  %p\n - %d\n", s21_memchr(str1, 'n', 26), *(char
  // *)s21_memchr(str1, 'n', 26)); printf("memchr     =  %p\n - %d\n",
  // memchr(str1, 'n', 26), *(char *)memchr(str1, 'n', 26));
  ck_assert(s21_memchr(str1, 'n', 26) == memchr(str1, 'n', 26));
}
END_TEST

START_TEST(s21_memchr_test2) {
  const char str1[] = "abcdefghijklmnopqrstuvwxyz";
  ck_assert(s21_memchr(str1, 'S', 26) == s21_NULL);
}
END_TEST

START_TEST(s21_memchr_test3) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  ck_assert(s21_memchr(str1, 358, 26) == memchr(str1, 'f', 26));
}
END_TEST

START_TEST(s21_memchr_test4) {
  char str1[] = "abcdefghijklmnopqrstuvwxyz";
  ck_assert(s21_memchr(str1, 'K', 5) == memchr(str1, 'k', 5));
}
END_TEST

Suite *s21_memchr_suite(void) {
  Suite *s;
  s = suite_create("s21_memchr");
  TCase *tc_memchr;
  tc_memchr = tcase_create("memchr");
  tcase_add_test(tc_memchr, s21_memchr_test1);
  tcase_add_test(tc_memchr, s21_memchr_test2);
  tcase_add_test(tc_memchr, s21_memchr_test3);
  tcase_add_test(tc_memchr, s21_memchr_test4);
  suite_add_tcase(s, tc_memchr);
  return s;
}

int s21_memchr_test(void) {
  Suite *s = s21_memchr_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}