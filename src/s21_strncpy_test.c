#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_strncpy_suite(void);
int s21_strncpy_test(void);

int main(void) {
  int count_failed = s21_strncpy_test();
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

START_TEST(s21_strncpy_test1) {
  char dest1[] = "_______ to School Magas!";
  char dest2[] = "_______ to School Magas!";
  char src[] = "Welcome";
  ck_assert(strcmp(s21_strncpy(dest1, src, 6), strncpy(dest2, src, 6)) == 0);
}
END_TEST

START_TEST(s21_strncpy_test2) {
  char dest1[] = "_______ to School Magas!";
  char dest2[] = "_______ to School Magas!";
  char src[] = "Welcome";
  ck_assert(strcmp(s21_strncpy(dest1, src, 1), strncpy(dest2, src, 1)) == 0);
}
END_TEST

START_TEST(s21_strncpy_test3) {
  char dest1[] = "Welcome";
  char dest2[] = "Welcome";
  char src[] = "Test";
  ck_assert(strcmp(s21_strncpy(dest1, src, 7), strncpy(dest2, src, 7)) == 0);
}
END_TEST

START_TEST(s21_strncpy_test4) {
  char dest1[] = "Hello";
  char dest2[] = "Hello";
  char src[] = "Welcome";
  ck_assert(strcmp(s21_strncpy(dest1, src, 4), strncpy(dest2, src, 4)) == 0);
}
END_TEST

START_TEST(s21_strncpy_test5) {
  char dest1[] = "Welcome";
  char dest2[] = "Welcome";
  char src[] = "";
  ck_assert(strcmp(s21_strncpy(dest1, src, 3), strncpy(dest2, src, 3)) == 0);
}
END_TEST

START_TEST(s21_strncpy_test6) {
  char dest1[] = "Welcome";
  char dest2[] = "Welcome";
  char src[] = "\0";
  ck_assert(strcmp(s21_strncpy(dest1, src, 2), strncpy(dest2, src, 2)) == 0);
}
END_TEST

Suite *s21_strncpy_suite(void) {
  Suite *s;
  s = suite_create("s21_strncpy");
  TCase *tc_strncpy;
  tc_strncpy = tcase_create("strncpy");
  tcase_add_test(tc_strncpy, s21_strncpy_test1);
  tcase_add_test(tc_strncpy, s21_strncpy_test2);
  tcase_add_test(tc_strncpy, s21_strncpy_test3);
  tcase_add_test(tc_strncpy, s21_strncpy_test4);
  tcase_add_test(tc_strncpy, s21_strncpy_test5);
  tcase_add_test(tc_strncpy, s21_strncpy_test6);
  suite_add_tcase(s, tc_strncpy);
  return s;
}

int s21_strncpy_test(void) {
  Suite *s = s21_strncpy_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}