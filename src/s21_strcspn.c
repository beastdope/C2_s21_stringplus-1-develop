#include "s21_string.h"

//  *
//  * Returns the length of the initial portion of str1
//  * that consists entirely of characters not found in str2.
//  *
//  * @param str1 the first string
//  * @param str2 the set of characters to be excluded
//  * @return the length of the initial portion of str1
//  *
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t length =
      0;  // это переменная, которая будет содержать длину начального сегмента
          // строки str1, который не содержит символы из строки str2.
  s21_size_t length_str_1 = s21_strlen(str1);
  s21_size_t length_str_2 = s21_strlen(str2);

  for (length = 0; length < length_str_1 && str1[length] != '\0'; length++) {
    for (s21_size_t j = 0; j < length_str_2; j++) {
      if (str1[length] == str2[j]) {
        return length;
      }
    }
  }
  return length;
}