#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_sscanf_suite(void);
int s21_sscanf_test(void);

int main(void) {
  int count_failed = s21_sscanf_test();
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

START_TEST(s21_sscanf_test1) {
  char *format = "%d %d";
  int d = 0;
  int d_ref = 0;
  int d1 = 0;
  int d1_ref = 0;
  char *str = "   1234 5678csdc";
  int cnt = 0;
  int cnt_ref = 0;

  cnt = s21_sscanf(str, format, &d, &d1);
  cnt_ref = sscanf(str, format, &d_ref, &d1_ref);
  /*printf("result for format:'%s'\n Expected: '%c' '%c'\n Actual:   "
                "'%c' '%c'\n Expected len: '%d'\n Actual len:   '%d'\n",
                format, d_ref, d1_ref, d, d1, cnt_ref, cnt);*/
  ck_assert_msg(
      cnt == cnt_ref && d == d_ref,
      "Invalid result for format:'%s'\n Expected: '%d' '%d'\n Actual:   "
      "'%d' '%d'\n Expected len: '%d'\n Actual len:   '%d'\n",
      format, d_ref, d, d1_ref, d1, cnt_ref, cnt);
}
END_TEST

START_TEST(s21_sscanf_test2) {
  char *format = "Test%i";
  int d = 0;
  int d_ref = 0;
  char *str = "   Test-1234";
  int cnt = 0;
  int cnt_ref = 0;

  cnt = s21_sscanf(str, format, &d);
  cnt_ref = sscanf(str, format, &d_ref);
  ck_assert_msg(cnt == cnt_ref && d == d_ref,
                "Invalid result for format:'%s'\n Expected: '%d'\n Actual:   "
                "'%d'\n Expected len: '%d'\n Actual len:   '%d'\n",
                format, d_ref, d, cnt_ref, cnt);
}
END_TEST

START_TEST(s21_sscanf_test3) {
  char *format = "Test%c %lc";
  char d = 0;
  char d_ref = 0;
  wchar_t d1 = 0;
  wchar_t d1_ref = 0;
  char *str = "TestX csdc";
  int cnt = 0;
  int cnt_ref = 0;
  cnt = s21_sscanf(str, format, &d, &d1);
  cnt_ref = sscanf(str, format, &d_ref, &d1_ref);
  ck_assert_msg(
      cnt == cnt_ref && d == d_ref,

      "Invalid result for format:'%s'\n Expected: '%c' '%lc'\n Actual:   "
      "'%c' '%lc'\n Expected len: '%d'\n Actual len:   '%d'\n",
      format, d_ref, d, d1_ref, d1, cnt_ref, cnt);
}
END_TEST

START_TEST(s21_sscanf_test4) {
  char *format = "Test%z";
  int d = 0;
  int d_ref = 0;
  char *str = "TestXcsdc";
  int cnt = 0;
  int cnt_ref = 0;

  cnt = s21_sscanf(str, format, &d);
  cnt_ref = sscanf(str, format, &d_ref);
  ck_assert_msg(cnt == cnt_ref && d == d_ref,
                "Invalid result for format:'%s'\n Expected: '%d'\n Actual:   "
                "'%d'\n Expected len: '%d'\n Actual len:   '%d'\n",
                format, d_ref, d, cnt_ref, cnt);
}
END_TEST

START_TEST(s21_sscanf_test5) {
  char *format = "Test%s %ls";
  char s[100] = {0};
  char s_ref[100] = {0};
  wchar_t ws[100] = {0};
  wchar_t ws_ref[100] = {0};
  char *str = "TestXcsdc asd";
  int cnt = 0;
  int cnt_ref = 0;
  cnt = s21_sscanf(str, format, &s, &ws);
  cnt_ref = sscanf(str, format, &s_ref, &ws_ref);
  ck_assert_msg(
      cnt == cnt_ref && strcmp(s, s_ref) == 0,
      "Invalid result for format:'%s'\n Expected: '%s %ls'\n Actual:   "
      "'%s %ls'\n Expected len: '%d'\n Actual len:   '%d'\n",
      format, s_ref, ws_ref, s, ws, cnt_ref, cnt);
}
END_TEST

START_TEST(s21_sscanf_test6) {
  char *format = "Tes  \t  %d %n";
  int d = 0;
  int d_ref = 0;
  int n = 0;
  char *str = "Tes  tX sd csdc";
  int cnt = 0;
  int cnt_ref = 0;
  int n_ref = 0;
  cnt = s21_sscanf(str, format, &d, &n);
  cnt_ref = sscanf(str, format, &d_ref, &n_ref);
  ck_assert_msg(
      cnt == cnt_ref && d == d_ref,
      "\nInvalid result for format:'%s'\n Expected: '%d %d'\n Actual:   "
      "'%d %d'\n Expected len: '%d'\n Actual len:   '%d'\n",
      format, d_ref, n_ref, d, n, cnt_ref, cnt);
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sscanf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_sscanf_test1);
  tcase_add_test(tc_core, s21_sscanf_test2);
  tcase_add_test(tc_core, s21_sscanf_test3);
  tcase_add_test(tc_core, s21_sscanf_test4);
  tcase_add_test(tc_core, s21_sscanf_test5);
  tcase_add_test(tc_core, s21_sscanf_test6);

  suite_add_tcase(s, tc_core);

  return s;
}

int s21_sscanf_test(void) {
  Suite *s = s21_sscanf_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}