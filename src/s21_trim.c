#include <stdlib.h>

#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = s21_NULL;
  if (src != s21_NULL) {
    const char *chars = " \t\r\n\v\f";
    if (trim_chars != s21_NULL && s21_strlen(trim_chars)) {
      chars = trim_chars;
    }
    const char *start = src;
    const char *end = (src + s21_strlen(src) - 1);
    for (int flag_start = 0, flag_end = 0;
         !(flag_start && flag_end) && (start <= end);) {
      if (s21_strchr(chars, *start)) {
        start++;
      } else {
        flag_start = 1;
      }
      if (s21_strchr(chars, *end)) {
        end--;
      } else {
        flag_end = 1;
      }
    }
    size_t res_len = (start > end) ? 0 : (end - start + 1);
    res = calloc(res_len + 1, sizeof(char));
    if (res != s21_NULL) {
      char *ptr = res;
      while (start <= end) {
        *ptr = *start;
        ptr++;
        start++;
      }
    }
  }
  return res;
}