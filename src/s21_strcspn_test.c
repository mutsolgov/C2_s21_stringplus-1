#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_strcspn_suite(void);
int s21_strcspn_test(void);

int main(void) {
  int count_failed = s21_strcspn_test();
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

START_TEST(s21_strcspn_test1) {
  char str1[] = "Welcome to School 21 Magas!";
  char str2[] = "School Ing";
  ck_assert(s21_strcspn(str1, str2) == strcspn(str1, str2));
}
END_TEST

START_TEST(s21_strcspn_test2) {
  char str1[] = "Welcome to School 21 Magas!";
  char str2[] = "0789";

  ck_assert(s21_strcspn(str1, str2) == strcspn(str1, str2));
}
END_TEST

START_TEST(s21_strcspn_test3) {
  char str1[] = "Welcome to School 21 Magas!";
  char str2[] = "Magas";

  ck_assert(s21_strcspn(str1, str2) == strcspn(str1, str2));
}
END_TEST

START_TEST(s21_strcspn_test4) {
  char str1[] = "Welcome to School 21 Magas!";
  char str2[] = "\0";

  ck_assert(s21_strcspn(str1, str2) == strcspn(str1, str2));
}
END_TEST

START_TEST(s21_strcspn_test5) {
  char str1[] = "Welcome to School 21 Magas!";
  char str2[] = "";

  ck_assert(s21_strcspn(str1, str2) == strcspn(str1, str2));
}
END_TEST

START_TEST(s21_strcspn_test6) {
  char str1[] = "";
  char str2[] = "Welcome to School 21 Magas!";

  ck_assert(s21_strcspn(str1, str2) == strcspn(str1, str2));
}
END_TEST

Suite *s21_strcspn_suite(void) {
  Suite *s;
  s = suite_create("s21_strcspn");
  TCase *tc_strcspn;
  tc_strcspn = tcase_create("strcspn");
  tcase_add_test(tc_strcspn, s21_strcspn_test1);
  tcase_add_test(tc_strcspn, s21_strcspn_test2);
  tcase_add_test(tc_strcspn, s21_strcspn_test3);
  tcase_add_test(tc_strcspn, s21_strcspn_test4);
  tcase_add_test(tc_strcspn, s21_strcspn_test5);
  tcase_add_test(tc_strcspn, s21_strcspn_test6);
  suite_add_tcase(s, tc_strcspn);
  return s;
}

int s21_strcspn_test(void) {
  Suite *s = s21_strcspn_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}