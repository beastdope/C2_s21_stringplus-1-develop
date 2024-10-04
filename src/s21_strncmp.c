#include "s21_string.h"
// ВОЗВРАЩАЕМЫЕ ЗНАЧЕНИЕ ФУНКЦИИ
// if_equal 0
// if_s2_less_s1 1
// if_s1_less_s2 -1
// чтобы имели представление что возвращает какой результат

int s21_strncmp(const char *str1, const char *str2,
                s21_size_t number_of_bytes) {
  int result = 0;
  int flag = 0;
  while (number_of_bytes != 0 && (*str1 != '\0' || *str2 != '\0') &&
         flag == 0) {  // пока кол-во байтов не равно 0 и
    // не достигнут конец строки
    if (*str1 == *str2) {  // сравниваем на равенство и если равные идем дальше
      str1++;
      str2++;
      number_of_bytes--;
    } else if (*str2 < *str1) {  // если str2 меньше str1 возвращаем 1 как в
                                 // документации
      result = 1;
      flag = 1;
    } else {  // также если str1 меньше str2 возвращаем -1
              // отрицательное целое
      result = -1;
      flag = 1;
    }
  }
  return result;  // если они равны возвращаем 0
}
