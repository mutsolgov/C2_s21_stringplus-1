#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  s21_size_t len = s21_strlen(dest);
  s21_size_t end;
  if (n > len)
    end = len;
  else
    end = n;
  for (s21_size_t j = 0; j < end; j++) {
    dest[j] = '\0';
  }

  while (i < n && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  if (*src == '\0') dest = "";
  return dest;
}