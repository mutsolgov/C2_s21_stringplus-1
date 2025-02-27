#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_strpbrk_suite(void);
int s21_strpbrk_test(void);

int main(void) {
  int count_failed = s21_strpbrk_test();
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

START_TEST(s21_strpbrk_test1) {
  char str1[] = "Welcome to School 21 Magas!";
  char str2[] = "l";
  ck_assert(strcmp(s21_strpbrk(str1, str2), strpbrk(str1, str2)) == 0);
}
END_TEST

START_TEST(s21_strpbrk_test2) {
  char str1[] = "Welcome to School 21 Magas!";
  char str2[] = "N";
  ck_assert(s21_strpbrk(str1, str2) == s21_NULL &&
            strpbrk(str1, str2) == s21_NULL);
}
END_TEST

START_TEST(s21_strpbrk_test3) {
  char str1[] = "Welcome to School 21 Magas!";
  char str2[] = "o";
  ck_assert(strcmp(s21_strpbrk(str1, str2), strpbrk(str1, str2)) == 0);
}
END_TEST

START_TEST(s21_strpbrk_test4) {
  char str1[] = "Welcome to School 21 Magas!";
  char str2[] = "";
  ck_assert(s21_strpbrk(str1, str2) == s21_NULL &&
            strpbrk(str1, str2) == s21_NULL);
}
END_TEST

START_TEST(s21_strpbrk_test5) {
  char str1[] = "";
  char str2[] = "";
  ck_assert(s21_strpbrk(str1, str2) == s21_NULL &&
            strpbrk(str1, str2) == s21_NULL);
}
END_TEST

START_TEST(s21_strpbrk_test6) {
  char str1[] = "";
  char str2[] = "Welcome to School 21 Magas!";
  ck_assert(s21_strpbrk(str1, str2) == s21_NULL &&
            strpbrk(str1, str2) == s21_NULL);
}
END_TEST

START_TEST(s21_strpbrk_test7) {
  char str1[] = "\0";
  char str2[] = "Welcome";
  ck_assert(s21_strpbrk(str1, str2) == s21_NULL &&
            strpbrk(str1, str2) == s21_NULL);
}
END_TEST

START_TEST(s21_strpbrk_test8) {
  char str1[] = "\n\n";
  char str2[] = "\n";
  ck_assert(strcmp(s21_strpbrk(str1, str2), strpbrk(str1, str2)) == 0);
}
END_TEST

Suite *s21_strpbrk_suite(void) {
  Suite *s;
  s = suite_create("s21_strpbrk");
  TCase *tc_strpbrk;
  tc_strpbrk = tcase_create("strpbrk");
  tcase_add_test(tc_strpbrk, s21_strpbrk_test1);
  tcase_add_test(tc_strpbrk, s21_strpbrk_test2);
  tcase_add_test(tc_strpbrk, s21_strpbrk_test3);
  tcase_add_test(tc_strpbrk, s21_strpbrk_test4);
  tcase_add_test(tc_strpbrk, s21_strpbrk_test5);
  tcase_add_test(tc_strpbrk, s21_strpbrk_test6);
  tcase_add_test(tc_strpbrk, s21_strpbrk_test7);
  tcase_add_test(tc_strpbrk, s21_strpbrk_test8);
  suite_add_tcase(s, tc_strpbrk);
  return s;
}

int s21_strpbrk_test(void) {
  Suite *s = s21_strpbrk_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}