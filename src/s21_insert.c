#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int error = 0;
  char *result = s21_NULL;
  if (src && str && start_index <= (s21_strlen(src))) {
    s21_size_t length = s21_strlen(src);
    s21_size_t len = s21_strlen(str);
    result = (char *)calloc(length + len + 1, sizeof(char));
    for (s21_size_t i = 0; i < start_index; i++) {
      result[i] = src[i];
    }
    for (s21_size_t i = 0; i < len; i++) {
      result[i + start_index] = str[i];
    }
    for (s21_size_t i = 0; i < length - start_index; i++) {
      result[i + start_index + len] = src[i + start_index];
    }
  } else {
    error = 1;
  }
  return error ? s21_NULL : (void *)result;
}
