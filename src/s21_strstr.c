#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  int flag = 0;
  char *res = s21_NULL;
  for (s21_size_t i = 0; haystack[i] != '\0'; ++i) {
    if (haystack[i] == needle[0]) flag = 0;
    for (s21_size_t j = 0; needle[j] != '\0'; ++j) {
      if (haystack[i + j] != needle[j]) {
        flag = 1;
        break;
      }
    }
    if (flag == 0) res = (char *)haystack + i;
  }
  return res;
}
