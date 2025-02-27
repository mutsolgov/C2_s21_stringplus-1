#include <check.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

Suite *s21_sprintf_suite(void);
int s21_sprintf_test(void);

int main(void) {
  int count_failed = s21_sprintf_test();
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

START_TEST(s21_sprintf_test1) {
  char *format = "Test string %%d:%d %c %15.5s % +-#0.0%%%d: %%m";
  int d = 666;
  char c = 'x';
  char *s = "teststring";
  int str1_len = 0;
  char str1[1000] = {0};
  int str2_len = {0};
  char str2[1000] = {0};
  str1_len = s21_sprintf(str1, format, d, c, s);
  str2_len = sprintf(str2, format, d, c, s);

  ck_assert_msg(str1_len == str2_len && strcmp(str1, str2) == 0,
                "\nФорматная срока:'%s'\n Результат s21_sprintf: '%s'\n "
                "Результат sprintf:'%s'\n"
                " Длина s21_sprintf: '%d'\n Длина sprintf: '%d'\n",
                format, str1, str2, str1_len, str2_len);
}
END_TEST

START_TEST(s21_sprintf_test2) {
  char *format = "Test string %%d: %d %%c: %c %%15.5s: %15.5s %%e: %e ";
  int d = 666;
  char c = 'x';
  char *s = "STRING";
  double e = 123456789.123456789;
  int str1_len = 0;
  char str1[1000] = {0};
  int str2_len = {0};
  char str2[1000] = {0};
  str1_len = s21_sprintf(str1, format, d, c, s, e);
  str2_len = sprintf(str2, format, d, c, s, e);

  ck_assert_msg(str1_len == str2_len && strcmp(str1, str2) == 0,
                "\nФорматная срока:'%s'\n Результат s21_sprintf: '%s'\n "
                "Результат sprintf:'%s'\n"
                " Длина s21_sprintf: '%d'\n Длина sprintf: '%d'\n",
                format, str1, str2, str1_len, str2_len);
}
END_TEST

START_TEST(s21_sprintf_test3) {
  char *format =
      "Test string %%c: %c %%d: %d %%i: %i %%e: %e %%E: %E %%f: %f %%g: %g "
      "%%G: %G %%o: %o %%s: %s %%u: %u %%x: %x %%X: %X %%p: %p %%n: %n";
  int d = 666;
  char c = 'x';
  char *s = "STRING";
  double e = 123456789.123456789;
  int n = 0;
  int str1_len = 0;
  char str1[2000] = {0};

  int str2_len = {0};
  char str2[2000] = {0};
  str1_len =
      s21_sprintf(str1, format, c, d, d, e, e, e, e, e, d, s, s, s, s, &d, &n);
  str2_len =
      sprintf(str2, format, c, d, d, e, e, e, e, e, d, s, s, s, s, &d, &n);

  ck_assert_msg(str1_len == str2_len && strcmp(str1, str2) == 0,
                "\nФорматная срока:'%s'\n Результат s21_sprintf: '%s'\n "
                "Результат sprintf:'%s'\n"
                " Длина s21_sprintf: '%d'\n Длина sprintf: '%d'\n",
                format, str1, str2, str1_len, str2_len);
}
END_TEST

START_TEST(s21_sprintf_test4) {
  char *format =
      "Test string %%c: %+- #07.2c %%d: %+- #07.2d %%i: %+- #07.2i %%e: %+- "
      "#07.2e "
      "%%E: %+- #07.2E "
      "%%f: %+- #07.2f %%g: %+- #07.2g "
      "%%G: %+- #07.2G %%o: %+- #07.2o %%s: %+- #07.2s %%u: %+- #07.2u %%x: "
      "%+- #07.2x "
      "%%X: %+- #07.2X "
      "%%p: %+- #07.2p "
      "%%n: %+- #07.2n %%m";
  int d = 666;
  char c = 'x';
  char *s = "STRING";
  double e = 123456789.123456789;
  int n = 0;
  int str1_len = 0;
  char str1[2000] = {0};
  int str2_len = {0};
  char str2[2000] = {0};
  str1_len =
      s21_sprintf(str1, format, c, d, d, e, e, e, e, e, d, s, s, s, s, &d, &n);
  str2_len =
      sprintf(str2, format, c, d, d, e, e, e, e, e, d, s, s, s, s, &d, &n);

  ck_assert_msg(str1_len == str2_len && strcmp(str1, str2) == 0,
                "\nФорматная срока:'%s'\n Результат s21_sprintf: '%s'\n "
                "Результат sprintf:'%s'\n"
                " Длина s21_sprintf: '%d'\n Длина sprintf: '%d'\n",
                format, str1, str2, str1_len, str2_len);
}
END_TEST

Suite *s21_sprintf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sprintf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_sprintf_test1);
  tcase_add_test(tc_core, s21_sprintf_test2);
  tcase_add_test(tc_core, s21_sprintf_test3);
  tcase_add_test(tc_core, s21_sprintf_test4);

  suite_add_tcase(s, tc_core);

  return s;
}

int s21_sprintf_test(void) {
  Suite *s = s21_sprintf_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return count_failed;
}