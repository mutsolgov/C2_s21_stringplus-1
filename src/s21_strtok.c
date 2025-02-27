#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  unsigned char flag[65536] = {0};
  while (*delim) {
    flag[(unsigned char)*delim] = 1;
    delim++;
  }
  static char *ptr = s21_NULL;
  char *token;
  char *rest;
  if (str != s21_NULL) {
    token = str;
    while (*token && flag[(unsigned char)*token]) token++;
    ptr = token;
  } else
    token = ptr;

  while (ptr && *ptr && !flag[(unsigned char)*ptr]) ptr++;
  rest = ptr;
  while (ptr && *ptr && flag[(unsigned char)*ptr]) ptr++;
  if (rest != s21_NULL) {
    *rest = '\0';
  }

  return *token ? token : s21_NULL;
}