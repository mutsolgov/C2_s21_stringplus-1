#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t size = 0;
  int flag = 0;
  if (str1 != s21_NULL && str2 != s21_NULL) {
    for (int i = 0; str1[i] != '\0' && !flag; ++i) {
      for (int j = 0; str2[j] != '\0' && !flag; ++j) {
        if (str1[i] == str2[j]) flag = 1;
      }
      if (!flag) size++;
    }
  }
  return size;
}