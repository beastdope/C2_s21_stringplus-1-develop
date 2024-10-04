#include "s21_string.h"

/**
 * Returns a pointer to the last occurrence of a character in a string.
 *
 * @param str the string to search
 * @param c the character to search for
 * @return a pointer to the last occurrence of c in str, or NULL if c does not
 * occur in str
 */
char *s21_strrchr(const char *str, int c) {
  // Инициализация указателя для отслеживания последнего вхождения символа
  const char *lastOccurrence = s21_NULL;

  // Перебор каждого символа в строке до достижения нулевого символа
  // (завершающего нуля)
  while (*str) {
    // Проверка, совпадает ли текущий символ с целевым символом
    if (*str == c) {
      // Обновление указателя последнего вхождения до текущей позиции
      lastOccurrence = str;
    }
    // Переход к следующему символу в строке
    str++;
  }

  // Проверка символа в конце строки
  if (*str == c) {
    lastOccurrence = str;
  }

  // Возвращение указателя на последнее вхождение символа или NULL, если символ
  // не найден
  return (char *)lastOccurrence;
}