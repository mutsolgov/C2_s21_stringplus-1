#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *res = s21_NULL;
  int flag = 0;
  if (str != s21_NULL) {
    while (*str != '\0' && !flag) {
      if (*str == (unsigned char)c) {
        res = (char *)str;
        flag = 1;
      } else {
        str++;
      }
    }
  }
  if ((unsigned char)c == '\0') res = "";
  return (char *)res;
}