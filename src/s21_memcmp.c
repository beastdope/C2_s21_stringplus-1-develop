#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int flag = 0;
  s21_size_t i = 0;

  const unsigned char *source1 =
      str1;  // объявляет указатель на беззнаковый символ и присваивает ему
             // значение указателя на массив символов str1
  const unsigned char *source2 =
      str2;  // объявляет указатель на беззнаковый символ и присваивает ему
             // значение указателя на массив символов str2

  while (i < n && flag == 0) {
    if (source1[i] != source2[i]) {
      flag = source1[i] - source2[i];
    }
    i++;
  }

  return flag;
}