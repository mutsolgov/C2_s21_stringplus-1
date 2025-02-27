#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = s21_NULL;
  for (s21_size_t i = 0; str1[i] != '\0' && !res; ++i) {
    for (s21_size_t j = 0; str2[j] != '\0' && !res; ++j) {
      if (str1[i] == str2[j]) {
        res = (char *)(str1 + i);
      }
    }
  }
  if (str1 == s21_NULL || str2 == s21_NULL) res = "";
  return (char *)res;
}