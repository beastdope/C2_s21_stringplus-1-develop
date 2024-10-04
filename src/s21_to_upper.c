#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *array = s21_NULL;
  int length = 0;
  if (str) {
    length = s21_strlen(str);
    array = (char *)calloc(length + 1, sizeof(char));
  }
  if (array) {
    s21_strncpy(array, str, length);
    for (s21_size_t i = 0; i < s21_strlen(array); i++) {
      if (array[i] >= 97 && array[i] <= 122) {
        array[i] -= 32;
      }
    }
  }
  return (void *)array;  // Возвращаем указатель на новую строку
}
