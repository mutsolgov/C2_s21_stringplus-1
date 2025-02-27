#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_strtok_suite(void);
int s21_strtok_test(void);

int main(void) {
  int count_failed = s21_strtok_test();
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

START_TEST(s21_strtok_test1) {
  char str1[] = "Welcome/to School 21 Magas!";
  char str2[] = "Welcome/to School 21 Magas!";
  char delim[] = "/";
  ck_assert(strcmp(s21_strtok(str1, delim), strtok(str2, delim)) == 0);
  ck_assert(strcmp(s21_strtok(s21_NULL, delim), strtok(s21_NULL, delim)) == 0);
  ck_assert(s21_strtok(s21_NULL, delim) == s21_NULL &&
            strtok(s21_NULL, delim) == s21_NULL);
}
END_TEST

START_TEST(s21_strtok_test2) {
  char str1[] = "DELIMDELIMWelcome to DELIMSchoolDELIM Magas Ing!";
  char str2[] = "DELIMDELIMWelcome to DELIMSchoolDELIM Magas Ing!";
  char delim[] = "DELI";
  // printf("s21 = %s\n", s21_strtok(str1, delim));
  // printf("2 = %s\n", s21_strtok(s21_NULL, delim));
  // printf("3 = %s\n", s21_strtok(s21_NULL, delim));
  // printf("4 = %s\n", s21_strtok(s21_NULL, delim));
  // printf("str = %s\n", strtok(str2, delim));
  // printf("2 = %s\n", strtok(s21_NULL, delim));
  // printf("3 = %s\n", strtok(s21_NULL, delim));
  // printf("4 = %s\n", strtok(s21_NULL, delim));
  ck_assert(strcmp(s21_strtok(str1, delim), strtok(str2, delim)) == 0);
  ck_assert(strcmp(s21_strtok(s21_NULL, delim), strtok(s21_NULL, delim)) == 0);
  ck_assert(strcmp(s21_strtok(s21_NULL, delim), strtok(s21_NULL, delim)) == 0);
  ck_assert(strcmp(s21_strtok(s21_NULL, delim), strtok(s21_NULL, delim)) == 0);
}
END_TEST

START_TEST(s21_strtok_test3) {
  char str1[] = "Welcome# to School$ Magas| Ing!";
  char str2[] = "Welcome# to School$ Magas| Ing!";
  char delim[] = "#$|";
  ck_assert(strcmp(s21_strtok(str1, delim), strtok(str2, delim)) == 0);
  ck_assert(strcmp(s21_strtok(s21_NULL, delim), strtok(s21_NULL, delim)) == 0);
  ck_assert(strcmp(s21_strtok(s21_NULL, delim), strtok(s21_NULL, delim)) == 0);
  ck_assert(strcmp(s21_strtok(s21_NULL, delim), strtok(s21_NULL, delim)) == 0);
  ck_assert(s21_strtok(s21_NULL, delim) == s21_NULL &&
            strtok(s21_NULL, delim) == s21_NULL);
}
END_TEST

Suite *s21_strtok_suite(void) {
  Suite *s;
  s = suite_create("s21_strtok");
  TCase *tc_strtok;
  tc_strtok = tcase_create("strtok");
  tcase_add_test(tc_strtok, s21_strtok_test1);
  tcase_add_test(tc_strtok, s21_strtok_test2);
  tcase_add_test(tc_strtok, s21_strtok_test3);
  suite_add_tcase(s, tc_strtok);
  return s;
}

int s21_strtok_test(void) {
  Suite *s = s21_strtok_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}