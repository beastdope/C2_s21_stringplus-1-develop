#include "s21_string.h"

/**
 * Returns the length of the initial segment of a string consisting entirely of
 * characters from the set of characters specified by `delim`.
 * @param str the string to search in
 * @param delim the set of characters to search for
 * @return the length of the initial segment of `str`
 */
s21_size_t s21_strspn(const char *str, const char *delim) {
  s21_size_t count = 0;
  while (*str && s21_strchr(delim, *str)) {
    count++;
    str++;
  }
  return count;
}

/**
 * Returns a pointer to the next token in a string.
 * @param str the string to search in
 * @param delim the set of characters to search for
 * @return a pointer to the next token in str, or s21_NULL if no more tokens are
 * found
 */
char *s21_strtok(char *str, const char *delim) {
  static char *previous_run =
      s21_NULL;  // the previous run of characters that were found

  if (str == s21_NULL) {  //  здесь мы смотрим передана ли строка для
                          //  токенезации, если str == s21_NULL, то мы назначаем
                          //  ей предыдущий резульатт из previous_run
    str = previous_run;     // the previous run of characters that were found
    if (str == s21_NULL) {  // если все-таки закончится строка для токенизации,
                            // например когда все слова будут токенизированы, мы
                            // возращаем нулевой указатель и привет функции...
      return s21_NULL;      // конец...
    }
  }

  str += s21_strspn(
      str,
      delim);  // Эта строка кода сдвигает указатель str на количество символов,
               // которые являются разделителями и находятся в начале строки.

  if (previous_run != s21_NULL &&
      *previous_run !=
          '\0') {  // Если previous_run указывает на непустой токен, то функция
                   // сбрасывает previous_run в s21_NULL и возвращает s21_NULL.
                   // Это означает, что токенизация завершена.

    previous_run = s21_NULL;
    return previous_run;
  }

  previous_run =
      str + s21_strcspn(
                str, delim);  // Эта строка кода находит следующий
                              // разделительный символ и обновляет previous_run
                              // так, чтобы он указывал на этот символ.

  if (previous_run != s21_NULL &&
      *previous_run !=
          '\0') {  // Если найден токен (разделительный символ не нулевой), то
                   // он обрезается (заменяется на \0), и previous_run
                   // устанавливается на следующий символ. В противном случае
                   // previous_run сбрасывается в s21_NULL.

    *previous_run = '\0';
    previous_run++;
  } else {
    previous_run = s21_NULL;
  }

  return str;  // В конце функции возвращается указатель на начало текущего
               // токена.
}
