#include "s21_string.h"

char *s21_strncpy(char *toHere, const char *fromHere, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n; i++) {
    toHere[i] = fromHere[i];
  }
  toHere[n] = '\0';
  return toHere;
}
