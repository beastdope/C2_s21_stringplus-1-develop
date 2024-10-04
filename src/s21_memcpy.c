#include "s21_string.h"

void *s21_memcpy(void *destination, const void *source,
                 s21_size_t number_of_bites_to_copy) {
  const char *src = source;      // определяем откуда
  char *where_to = destination;  // определяем куда
  while (number_of_bites_to_copy--)
    *where_to++ = *src++;  // пока байты не закончатся делаем копирование

  return destination;  // возвращаем указатель на начальную область памяти в
                       // которую скопировали данные
}
