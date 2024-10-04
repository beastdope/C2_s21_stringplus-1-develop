#include <math.h>

#include "s21_string.h"

/**
 * Формирует выходную строку в соответствии с формат-строкой (format) и
 * записывает её в память по указателю (str).
 * @param str - Это С-строка, которую функция обрабатывает в качестве источника
 * для извлечения данных;
 * @param format - это С-строка, содержащая один или несколько следующих
 * элементов: пробельный символ, непробельный символ и спецификаторы формата.
 * Спецификатор формата следует прототипу:
 * %[флаги][ширина][.точность][длина]спецификатор.
 * @param ... - прочие аргументы, которые могут быть подставлены на место
 * соответствующих спецификаторов.
 * @return в случае успеха - число записанных символов (за исключением символа
 * конца строки), в случае неудачи - целое отрицательное число
 */
int s21_sprintf(char* str, const char* format, ...) {
  char* start_of_str = str;

  va_list arguments;
  va_start(arguments, format);

  int flag_error = 0;
  while (!flag_error && *format) {
    if (*format != '%') {
      *str = *format;
      str++;
    } else {
      format++;
      spec curr_spec = {0};
      format = parse_spec(format, &curr_spec, &arguments);
      if (curr_spec.not_correct) flag_error = 1;
      str = spec_to_str(str, &curr_spec, &arguments);
    }
    format++;
  }

  int result;
  if (flag_error) {
    result = -1;
  } else {
    *str = '\0';
    result = str - start_of_str;
  }
  va_end(arguments);
  return result;
}

// Начало. Парсинг спецификаторов

const char* parse_spec(const char* str, spec* curr_spec, va_list* args) {
  str = parse_flags(str, curr_spec);
  str = parse_width(str, curr_spec, args);
  str = parse_accuracy(str, curr_spec, args);
  str = parse_length_type(str, curr_spec);
  str = parse_symbol(str, curr_spec);

  return str;
}

const char* parse_flags(const char* str, spec* curr_spec) {
  int flag_continue = 1;
  while (flag_continue && *str) {
    if (*str == '+') {
      curr_spec->f_plus = 1;
      str++;
    } else if (*str == '-') {
      curr_spec->f_minus = 1;
      str++;
    } else if (*str == ' ') {
      curr_spec->f_space = 1;
      str++;
    } else if (*str == '#') {
      curr_spec->f_hash = 1;
      str++;
    } else if (*str == '0') {
      curr_spec->f_zero = 1;
      str++;
    } else {
      flag_continue = 0;
    }
  }

  // обработка конфликтующих флагов
  if (curr_spec->f_plus && curr_spec->f_space) curr_spec->f_space = 0;
  if (curr_spec->f_minus && curr_spec->f_zero) curr_spec->f_zero = 0;

  return str;
}

const char* parse_width(const char* str, spec* curr_spec, va_list* args) {
  if (*str == '*') {
    curr_spec->width = va_arg(*args, int);
    str++;
  } else {
    str = parse_num(str, &(curr_spec->width));
  }

  return str;
}

const char* parse_accuracy(const char* str, spec* curr_spec, va_list* args) {
  curr_spec->accuracy = 1;
  curr_spec->f_accuracy = 1;

  if (*str == '.') {
    curr_spec->accuracy = 0;
    curr_spec->f_accuracy = 0;
    str++;
    if (*str == '*') {
      curr_spec->accuracy = va_arg(*args, int);
      str++;
    } else {
      str = parse_num(str, &(curr_spec->accuracy));
    }
  }

  return str;
}

const char* parse_num(const char* str, s21_size_t* dst) {
  int flag_continue = 1;
  while (flag_continue && *str) {
    if ('0' <= *str && *str <= '9') {
      *dst = *dst * 10 + (*str - '0');
      str++;
    } else {
      flag_continue = 0;
    }
  }

  return str;
}

const char* parse_length_type(const char* str, spec* curr_spec) {
  if (*str == 'h' || *str == 'l' || *str == 'L') {
    curr_spec->len_type = *str;
    str++;
  }

  return str;
}

const char* parse_symbol(const char* str, spec* curr_spec) {
  const char spec_chars[] = "cdfsuxXop%";

  if (s21_strchr(spec_chars, *str) != s21_NULL) {
    curr_spec->symbol = *str;
    if (curr_spec->symbol == 's' && curr_spec->f_accuracy)
      curr_spec->accuracy = 0;
    else if (curr_spec->symbol == 'f' && curr_spec->f_accuracy)
      curr_spec->accuracy = 6;
    else if (!curr_spec->f_accuracy &&
             (curr_spec->symbol == 'd' || curr_spec->symbol == 'u' ||
              curr_spec->symbol == 'o' || curr_spec->symbol == 'x' ||
              curr_spec->symbol == 'X')) {
      curr_spec->f_zero = 0;
      // из-за сообщения компилятора: "'0' flag ignored with precision
      // (gnu_printf format)" (относится к целым числам)
    }
  } else {
    curr_spec->not_correct = 1;
  }

  return str;
}

char* spec_to_str(char* str, spec* curr_spec, va_list* args) {
  char type = curr_spec->symbol;

  if (type == 'd') {
    str = print_int(str, curr_spec, args);
  } else if (type == 'u' || type == 'x' || type == 'X' || type == 'o') {
    str = print_unsigned_int(str, curr_spec, args);
  } else if (type == 'c') {
    str = print_char(str, curr_spec, args);
  } else if (type == 's') {
    str = print_string(str, curr_spec, args);
  } else if (type == '%') {
    *str = '%';
    str++;
  } else if (type == 'f') {
    str = print_float(str, curr_spec, args);
  } else if (type == 'p') {
    str = print_pointer(str, curr_spec, args);
  }

  return str;
}

// Конец. Парсинг спецификаторов

// Начало. Функции печати спецификаторов

char* print_int(char* str, spec* curr_spec, va_list* args) {
  long int val = 0;
  if (curr_spec->len_type == 'h') {
    val = (short)va_arg(*args, int);
  } else if (curr_spec->len_type == 'l') {
    val = (long int)va_arg(*args, long int);
  } else {
    val = (int)va_arg(*args, int);
  }

  s21_size_t buf_size = calc_size_int(curr_spec, val);
  char* buffer = calloc(buf_size, sizeof(char));
  if (buffer != s21_NULL) {
    print_inv_buf_int(buffer, curr_spec, val);
  }

  while (buf_size > 0) {
    buf_size--;
    *str = *(buffer + buf_size);
    str++;
  }

  free(buffer);
  return str;
}

char* print_unsigned_int(char* str, spec* curr_spec, va_list* args) {
  long int val = 0;
  if (curr_spec->len_type == 'h') {
    val = (unsigned short)va_arg(*args, unsigned int);
  } else if (curr_spec->len_type == 'l') {
    val = (unsigned long int)va_arg(*args, unsigned long int);
  } else {
    val = (unsigned int)va_arg(*args, unsigned int);
  }

  int base;
  if (curr_spec->symbol == 'o')
    base = BASE_8;
  else if (curr_spec->symbol == 'u')
    base = BASE_10;
  else
    base = BASE_16;

  s21_size_t buf_size = calc_size_unsigned_int(curr_spec, val, base);

  char* buffer = calloc(buf_size, sizeof(char));
  if (buffer != s21_NULL) {
    print_inv_buf_unsigned_int(buffer, curr_spec, val, base);
  }

  while (buf_size > 0) {
    buf_size--;
    *str = *(buffer + buf_size);
    str++;
  }

  free(buffer);
  return str;
}

char* print_float(char* str, spec* curr_spec, va_list* args) {
  long double val = 0;
  if (curr_spec->len_type == 'L') {
    val = (long double)va_arg(*args, long double);
  } else {
    val = (double)va_arg(*args, double);
  }

  s21_size_t buf_size = calc_size_float(curr_spec, val);
  char* buffer = calloc(buf_size, sizeof(char));
  if (buffer != s21_NULL) {
    s21_size_t counter = 0;
    if (isnan(val)) {
      counter = decompose_print_float_nan(buffer, val);
      decompose_add_spaces(buffer, curr_spec, counter);
    } else if (isinf(val)) {
      counter = decompose_print_float_inf(buffer, val);
      decompose_add_spaces(buffer, curr_spec, counter);
    } else {
      counter = decompose_print_float_abs_num(buffer, curr_spec, val);
      decompose_sign_and_fillers_float(buffer, curr_spec, counter, val);
    }
  }

  for (s21_size_t i = 0; i < buf_size; i++, str++) *str = *(buffer + i);

  free(buffer);
  return str;
}

char* print_char(char* str, spec* curr_spec, va_list* args) {
  char symbol = (char)va_arg(*args, int);

  if (curr_spec->f_minus) {
    *str = symbol;
    str++;
  }

  s21_size_t diff = 0;
  if (curr_spec->width > 1) diff = curr_spec->width - 1;

  while (diff > 0) {
    *str = ' ';
    str++;
    diff--;
  }

  if (!curr_spec->f_minus) {
    *str = symbol;
    str++;
  }

  return str;
}

char* print_string(char* str, spec* curr_spec, va_list* args) {
  char* stroka = (char*)va_arg(*args, char*);
  s21_size_t len = s21_strlen(stroka);

  if (curr_spec->f_minus) {
    if (curr_spec->accuracy == 0) {
      for (s21_size_t i = 0; i < len; i++, str++, stroka++) *str = *stroka;
      for (; len < curr_spec->width; str++, len++) *str = ' ';
    } else {
      for (s21_size_t i = 0; i < len && i < curr_spec->accuracy;
           i++, str++, stroka++)
        *str = *stroka;
      len = len < curr_spec->accuracy ? len : curr_spec->accuracy;
      for (; len < curr_spec->width; str++, len++) *str = ' ';
    }
  } else {
    if (curr_spec->accuracy == 0) {
      for (s21_size_t i = 0; i + len < curr_spec->width; i++, str++) *str = ' ';
      for (s21_size_t i = 0; i < len; i++, str++, stroka++) *str = *stroka;

    } else {
      s21_size_t limit = len < curr_spec->accuracy ? len : curr_spec->accuracy;
      for (s21_size_t i = 0; i + limit < curr_spec->width; i++, str++)
        *str = ' ';
      for (s21_size_t i = 0; i < len && i < curr_spec->accuracy;
           i++, str++, stroka++)
        *str = *stroka;
    }
  }

  return str;
}

char* print_pointer(char* str, spec* curr_spec, va_list* args) {
  unsigned long int value = (unsigned long int)va_arg(*args, unsigned long int);
  if ((void*)value != s21_NULL) {
    curr_spec->symbol = 'x';
    curr_spec->f_hash = 1;
    curr_spec->len_type = 'l';
    s21_size_t buf_size = calc_size_unsigned_int(curr_spec, value, BASE_16);

    char* buffer = calloc(buf_size, sizeof(char));
    if (buffer != s21_NULL) {
      print_inv_buf_unsigned_int(buffer, curr_spec, value, BASE_16);
    }

    while (buf_size > 0) {
      buf_size--;
      *str = *(buffer + buf_size);
      str++;
    }

    free(buffer);
  } else {
    s21_size_t msg_lenght = s21_strlen("(nil)");
    s21_size_t buf_size =
        curr_spec->width > msg_lenght ? curr_spec->width : msg_lenght;

    char* buffer = calloc(buf_size, sizeof(char));
    if (buffer != s21_NULL) {
      decompose_print_float_nil(buffer);
      decompose_add_spaces(buffer, curr_spec, msg_lenght);
    }
    for (s21_size_t i = 0; i < buf_size; i++, str++) *str = *(buffer + i);

    free(buffer);
  }
  return str;
}

s21_size_t calc_size_int(spec* curr_spec, long int value) {
  s21_size_t res_size = 0;

  long int abs_value_copy = value >= 0 ? value : -value;
  while (abs_value_copy > 0) {
    res_size++;
    abs_value_copy /= 10;
  }
  if ((s21_size_t)curr_spec->accuracy > res_size)
    res_size = curr_spec->accuracy;
  if ((value < 0 || curr_spec->f_plus || curr_spec->f_space)) res_size++;
  if ((s21_size_t)curr_spec->width > res_size) res_size = curr_spec->width;

  return res_size;
}

s21_size_t calc_size_unsigned_int(spec* curr_spec, unsigned long int value,
                                  int base) {
  s21_size_t res_size = 0;
  unsigned long int value_copy = value;
  while (value_copy > 0) {
    res_size++;
    value_copy /= base;
  }

  if ((s21_size_t)curr_spec->accuracy > res_size)
    res_size = curr_spec->accuracy;

  if (curr_spec->f_hash && value != 0) {
    if ((char)curr_spec->symbol == 'o')
      res_size += 1;
    else
      res_size += 2;
  }
  if ((s21_size_t)curr_spec->width > res_size) res_size = curr_spec->width;

  return res_size;
}

s21_size_t calc_size_float(spec* curr_spec, long double value) {
  s21_size_t res_size = 0;

  if (isnan(value) || isinf(value)) {
    if (signbit(value))
      res_size = 4;
    else
      res_size = 3;
  } else {
    long double abs_value_copy = value >= 0 ? value : -value;
    while (abs_value_copy > 1) {
      res_size++;
      abs_value_copy /= 10;
    }
    if (res_size == 0) res_size = 1;  // если число было равно нулю
    if ((s21_size_t)curr_spec->accuracy > 0)
      res_size += curr_spec->accuracy + 1;
    if ((value < 0 || curr_spec->f_plus || curr_spec->f_space)) res_size++;
  }
  if ((s21_size_t)curr_spec->width > res_size) res_size = curr_spec->width;

  return res_size;
}

void print_inv_buf_int(char* buffer, spec* curr_spec, long int value) {
  char* buf_pointer_copy = buffer;
  long int abs_value_copy = value >= 0 ? value : -value;

  s21_size_t counter = decompose_print_inv_num(buf_pointer_copy, curr_spec,
                                               abs_value_copy, BASE_10);
  buf_pointer_copy += counter;
  decompose_sign_and_fillers_int(buffer, buf_pointer_copy, curr_spec, counter,
                                 value);
}

s21_size_t decompose_print_inv_num(char* buffer, spec* curr_spec,
                                   long int value, int base) {
  s21_size_t counter = 0;
  int flag_uppercase = curr_spec->symbol == 'X' ? 1 : 0;

  while (value > 0) {
    *buffer = digit_to_symbol(value % base, flag_uppercase);
    value /= base;
    counter++;
    buffer++;
  }

  return counter;
}

s21_size_t decompose_print_float_abs_num(char* buffer, spec* curr_spec,
                                         long double value) {
  s21_size_t counter = 0;
  long double abs_value_copy = value >= 0 ? value : -value;
  long double int_part_f, fract_part;

  fract_part = modfl(abs_value_copy, &int_part_f);

  long int int_part = (long int)int_part_f;
  if (int_part == 0) {
    *buffer = digit_to_symbol(0, 0);
    buffer++;
    counter++;
  } else {
    long int inv_int_part = inv_long_int(int_part);
    while (inv_int_part > 0) {
      *buffer = digit_to_symbol(inv_int_part % BASE_10, 0);
      inv_int_part /= BASE_10;
      buffer++;
      counter++;
    }
  }

  if (curr_spec->accuracy) {
    *buffer = '.';
    buffer++;
    counter++;

    long double power = pow(10, (long double)curr_spec->accuracy);
    fract_part = roundl(fract_part * power) / power;
    for (s21_size_t i = 0; i < curr_spec->accuracy; i++, buffer++, counter++) {
      fract_part *= BASE_10;
      *buffer = digit_to_symbol((int)(fract_part + 0.05) % BASE_10, 0);
      fract_part = modfl(fract_part, &int_part_f);
    }
  } else {
    if (curr_spec->f_hash) {
      *buffer = '.';
      counter++;
    }
  }
  return counter;
}

s21_size_t decompose_print_float_inf(char* buffer, long double value) {
  s21_size_t counter = 0;

  if (signbit(value)) {
    *buffer = '-';
    buffer++;
    counter++;
  }
  *buffer = 'i';
  *(buffer + 1) = 'n';
  *(buffer + 2) = 'f';
  counter += 3;

  return counter;
}

s21_size_t decompose_print_float_nan(char* buffer, long double value) {
  s21_size_t counter = 0;

  if (signbit(value)) {
    *buffer = '-';
    buffer++;
    counter++;
  }
  *buffer = 'n';
  *(buffer + 1) = 'a';
  *(buffer + 2) = 'n';
  counter += 3;

  return counter;
}

s21_size_t decompose_print_float_nil(char* buffer) {
  s21_size_t counter = 0;

  *buffer = '(';
  *(buffer + 1) = 'n';
  *(buffer + 2) = 'i';
  *(buffer + 3) = 'l';
  *(buffer + 4) = ')';
  counter += 5;

  return counter;
}

void decompose_sign_and_fillers_int(char* buffer_start, char* buffer_curr_pos,
                                    spec* curr_spec, s21_size_t counter,
                                    long int value) {
  s21_size_t diff =
      (curr_spec->accuracy > counter) ? (curr_spec->accuracy - counter) : 0;
  while (diff > 0) {
    *buffer_curr_pos = '0';
    buffer_curr_pos++;
    diff--;
  }

  char sign = is_sign_int(curr_spec, value);
  if (sign) {
    if (!curr_spec->f_zero) {
      *buffer_curr_pos = sign;
      buffer_curr_pos++;
    }
    curr_spec->accuracy++;
    counter++;
  }

  if (curr_spec->accuracy > counter)
    diff = (curr_spec->width > curr_spec->accuracy)
               ? (curr_spec->width - curr_spec->accuracy)
               : 0;
  else
    diff = (curr_spec->width > counter) ? (curr_spec->width - counter) : 0;

  if (diff > 0) {
    if (curr_spec->f_minus) {
      for (char* i = buffer_curr_pos - 1; i - buffer_start >= 0; i--)
        *(i + diff) = *i;
      for (s21_size_t i = 0; i < diff; i++) *(buffer_start + i) = ' ';
    } else {
      while (diff > 0) {
        if (curr_spec->f_zero)
          *buffer_curr_pos = '0';
        else
          *buffer_curr_pos = ' ';
        buffer_curr_pos++;
        diff--;
      }
    }
  }
  if (curr_spec->f_zero && sign) *buffer_curr_pos = sign;
}

void print_inv_buf_unsigned_int(char* buffer, spec* curr_spec, long int value,
                                int base) {
  char* buf_pointer_copy = buffer;
  long int abs_value_copy = value >= 0 ? value : -value;

  s21_size_t counter = decompose_print_inv_num(buf_pointer_copy, curr_spec,
                                               abs_value_copy, base);
  buf_pointer_copy += counter;
  decompose_prefix_and_fillers_uint(buffer, buf_pointer_copy, curr_spec,
                                    counter, value);
}

void decompose_prefix_and_fillers_uint(char* buffer_start,
                                       char* buffer_curr_pos, spec* curr_spec,
                                       s21_size_t counter, long int value) {
  s21_size_t diff =
      (curr_spec->accuracy > counter) ? (curr_spec->accuracy - counter) : 0;
  while (diff > 0) {
    *buffer_curr_pos = '0';
    buffer_curr_pos++;
    diff--;
  }

  if (curr_spec->f_hash && value != 0) {
    if (!curr_spec->f_zero)
      buffer_curr_pos =
          decompose_print_prefix_oct_and_hex(buffer_curr_pos, curr_spec);
    curr_spec->accuracy += curr_spec->symbol == 'o' ? 1 : 2;
    counter += curr_spec->symbol == 'o' ? 1 : 2;
  }

  if (curr_spec->accuracy > counter)
    diff = (curr_spec->width > curr_spec->accuracy)
               ? (curr_spec->width - curr_spec->accuracy)
               : 0;
  else
    diff = (curr_spec->width > counter) ? (curr_spec->width - counter) : 0;

  if (diff > 0) {
    if (curr_spec->f_minus) {
      for (char* i = buffer_curr_pos - 1; i - buffer_start >= 0; i--)
        *(i + diff) = *i;
      for (s21_size_t i = 0; i < diff; i++) *(buffer_start + i) = ' ';
    } else {
      while (diff > 0) {
        if (curr_spec->f_zero)
          *buffer_curr_pos = '0';
        else
          *buffer_curr_pos = ' ';
        buffer_curr_pos++;
        diff--;
      }
    }
  }
  if (curr_spec->f_zero && curr_spec->f_hash && value != 0)
    decompose_print_prefix_oct_and_hex(buffer_curr_pos, curr_spec);
}

char* decompose_print_prefix_oct_and_hex(char* buffer, spec* curr_spec) {
  if (curr_spec->symbol == 'x') {
    *buffer = 'x';
    buffer++;
  } else if (curr_spec->symbol == 'X') {
    *buffer = 'X';
    buffer++;
  }
  *buffer = '0';
  buffer++;

  return buffer;
}

void decompose_add_spaces(char* buffer, spec* curr_spec, s21_size_t counter) {
  s21_size_t diff =
      (curr_spec->width > counter) ? (curr_spec->width - counter) : 0;
  if (diff > 0) {
    if (curr_spec->f_minus) {
      buffer += counter;
      for (char* i = buffer; i < (buffer + diff); i++) *i = ' ';
    } else {
      char* index_of_last = buffer + (curr_spec->width - 1);
      for (char* i = index_of_last; i >= index_of_last - diff; i--)
        *i = *(i - diff);
      for (char* i = buffer; i < (buffer + diff); i++) *i = ' ';
    }
  }
}

void decompose_sign_and_fillers_float(char* buffer_start, spec* curr_spec,
                                      s21_size_t counter, long double value) {
  char* buffer_curr_pos = buffer_start + counter;
  char sign = is_sign_float(curr_spec, value);
  if (sign) {
    for (char* i = buffer_curr_pos; i > buffer_start; i--) *i = *(i - 1);
    buffer_curr_pos++;
    if (!curr_spec->f_zero) {
      *buffer_start = sign;
    }
    counter++;
  }

  s21_size_t diff =
      (curr_spec->width > counter) ? (curr_spec->width - counter) : 0;

  if (diff > 0) {
    if (curr_spec->f_minus) {
      for (char* i = buffer_curr_pos; i < (buffer_curr_pos + diff); i++)
        *i = ' ';
    } else {
      char* pos_of_last = buffer_curr_pos + diff - 1;
      for (char* i = pos_of_last; i > pos_of_last - counter; i--)
        *i = *(i - diff);

      char filler = curr_spec->f_zero ? '0' : ' ';
      char* start =
          (curr_spec->f_zero && sign) ? buffer_start + 1 : buffer_start;

      for (char* i = start; i < (start + diff); i++) *i = filler;
    }
  }
  if (curr_spec->f_zero && sign) *buffer_start = sign;
}

char is_sign_int(spec* curr_spec, long int value) {
  char sign = 0;

  if (value < 0) {
    sign = '-';
  } else if (curr_spec->f_plus) {
    sign = '+';
  } else if (curr_spec->f_space) {
    sign = ' ';
  }

  return sign;
}

char is_sign_float(spec* curr_spec, long double value) {
  char sign = 0;

  if (value < 0) {
    sign = '-';
  } else if (curr_spec->f_plus) {
    sign = '+';
  } else if (curr_spec->f_space) {
    sign = ' ';
  }

  return sign;
}

char digit_to_symbol(int digit, int flag_uppercase) {
  char res;

  if (digit < 10)
    res = digit + '0';
  else if (digit == 10)
    res = flag_uppercase ? 'A' : 'a';
  else if (digit == 11)
    res = flag_uppercase ? 'B' : 'b';
  else if (digit == 12)
    res = flag_uppercase ? 'C' : 'c';
  else if (digit == 13)
    res = flag_uppercase ? 'D' : 'd';
  else if (digit == 14)
    res = flag_uppercase ? 'E' : 'e';
  else if (digit == 15)
    res = flag_uppercase ? 'F' : 'f';

  return res;
}

long int inv_long_int(long int val) {
  long int res = 0;
  while (val > 0) {
    res = res * BASE_10 + val % BASE_10;
    val /= BASE_10;
  }
  return res;
}

// Конец. Функции печати спецификаторов
