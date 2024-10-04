#include "s21_string.h"

char *s21_strncat(char *destination, const char *source,
                  s21_size_t number_of_bytes) {
  // делаем указатель на целевую строку
  char *dest_end_of_string = destination + s21_strlen(destination);

  // добавляем символы исходной к целевой строке
  while (*source != '\0' &&
         number_of_bytes--) {  // пока не конец строки и пока байты не кончились
    *dest_end_of_string++ = *source++;  // добавляем символ к цели
  }

  // убеждаемся что целевая заканчивается нуль терминалом
  *dest_end_of_string = '\0';

  // возвращаем указатель на массив в который была добавлена строка
  return destination;
}