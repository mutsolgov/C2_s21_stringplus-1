#include <stdlib.h>

#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = s21_NULL;
  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  if (src != s21_NULL && str != s21_NULL && (start_index <= src_len)) {
    res = calloc(src_len + str_len + 1, sizeof(char));
    if (res != s21_NULL) {
      const char *start_ptr = src + start_index;
      char *ptr = res;
      while (*src || *str) {
        if (src < start_ptr || !(*str)) {
          *ptr = *src;
          src++;
        } else {
          *ptr = *str;
          str++;
        }
        ptr++;
      }
    }
  }
  return res;
}
