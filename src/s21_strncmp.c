#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  int flag = 0;
  if (str1 != s21_NULL && str2 != s21_NULL) {
    s21_size_t count = 0;
    while (count < n && (str1[count] != '\0' || str2[count] != '\0') && !flag) {
      if (str1[count] == str2[count]) {
        count++;
      } else {
        res = str1[count] - str2[count];
        flag = 1;
      }
    }
  }
  return res;
}