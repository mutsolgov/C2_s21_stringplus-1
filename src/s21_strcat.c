#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  char *ptr = dest;
  while (*dest) {
    dest++;
  }
  while ((*dest++ = *src++)) {
    ;
  }

  return ptr;
}