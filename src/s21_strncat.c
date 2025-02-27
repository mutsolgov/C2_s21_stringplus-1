#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t len = s21_strlen(dest);
  s21_memcpy(dest + len, src, n);
  dest[len + n] = '\0';
  return dest;
}