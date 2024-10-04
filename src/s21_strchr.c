#include "s21_string.h"

/**
 * Returns a pointer to the first occurrence of the character n in the string
 * str. If n is not found, the function returns s21_NULL.
 *
 * @param str the string to search in
 * @param n the character to search for
 * @return a pointer to the first occurrence of the character n in the string
 * str, or s21_NULL if n is not found
 */
char *s21_strchr(const char *str, int n) {
  const char *result = s21_NULL;
  int length = s21_strlen(str) + 1;  // length is the length of str plus 1
  for (int i = 0; i < length; i++) {
    if (str[i] == n) {
      result =
          (str +
           i);  // result is set to the address of the character that matches n
      break;
    }
  }
  return (char *)result;  // result is cast to a char* and returned
}
