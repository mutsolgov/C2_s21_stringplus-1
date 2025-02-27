#include "s21_string.h"

#define MEMORY_ERROR "MEMORY ERROR: Insufficient memory to allocate.\n"

void *s21_malloc(s21_size_t size) {
  // Our implementation of safe malloc process
  void *ptr = malloc(size);
  s21_is_nonull(ptr);

  return ptr;
}

void *s21_calloc(s21_size_t nmemb, s21_size_t size) {
  // Our implementation of safe calloc process
  void *ptr = calloc(nmemb, size);
  s21_is_nonull(ptr);

  return ptr;
}

void *s21_realloc(void *ptr, s21_size_t size) {
  // Our implementation of safe realloc process
  void *new_ptr = realloc(ptr, size);
  if (size != 0) {
    s21_is_nonull(new_ptr);
  }

  return new_ptr;
}

void s21_free(void *ptr) {
  // Our implementation of safe free process
  if (ptr != s21_NULL) free(ptr);
}

void s21_print_error() {
  fprintf(stderr, MEMORY_ERROR);
  exit(EXIT_FAILURE);
}

void s21_is_nonull(void *const ptr) {
  if (ptr == s21_NULL) {
    s21_print_error();
  }
}

void s21_add_null_ch(char *str, int index) { str[index] = '\0'; }
