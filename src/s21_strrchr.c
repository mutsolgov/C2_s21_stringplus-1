#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *res = s21_NULL;
  const char *begin = (char *)str;
  if (str != s21_NULL) {
    int flag = 0;
    while (*str) str++;

    do {
      if (*str == c) {
        res = (char *)str;
      }
      if (begin == str) {
        flag = 1;
      } else {
        str--;
      }
    } while (*str && !res && !flag);
  }
  return res;
}