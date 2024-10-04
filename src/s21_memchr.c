#include "s21_string.h"

void *s21_memchr(const void *src, int char_to_search, s21_size_t length) {
  if (length != 0) {
    const unsigned char *source =
        src;  // объявление указателя для поиска по блокам памяти
    do {
      if (*source++ == char_to_search)
        return ((void *)(source - 1));  // sourse - 1 это найденный (нынешний
                                        // знак) а не следующий знак(по
                                        // стандарту source это следующий знак)
    } while (--length != 0);  // пока не закончатся байты для поиска
  }
  return s21_NULL;  // по стандарту если знак не найдЭн или его нет возвращаем
                    // NULL
}