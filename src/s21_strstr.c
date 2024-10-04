#include "s21_string.h"

// /**
//  * strstr - finds the first occurrence of a substring in a string
//  * @haystack: pointer to the string to search in
//  * @needle: pointer to the substring to search for
//  *
//  * Returns a pointer to the first occurrence of the @needle in the @haystack,
//  * or NULL if the @needle is not found.
//  */
char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t i = 0;
  int flag = 1;
  for (; haystack[i] != '\0' && flag == 1; i++) {
    flag = 0;
    for (s21_size_t j = 0; needle[j] != '\0' && flag == 0; j++) {
      if ((haystack[i + j] == '\0') || (haystack[i + j] != needle[j])) {
        flag = 1;
      }
    }
  }
  i--;
  return flag ? s21_NULL : (char *)&haystack[i];
}
