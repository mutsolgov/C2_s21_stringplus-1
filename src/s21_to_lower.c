#include <stdlib.h>

#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *res = s21_NULL;
  if (str != s21_NULL) {
    res = calloc(s21_strlen(str) + 1, sizeof(char));
    if (res != s21_NULL) {
      char *ptr = res;
      while (*str) {
        if (*str >= 65 && *str <= 90)
          *ptr = *str + 32;
        else
          *ptr = *str;
        str++;
        ptr++;
      }
    }
  }
  return res;
}