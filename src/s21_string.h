#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_NULL (void*)0

typedef long unsigned s21_size_t;

s21_size_t s21_strlen(const char* str);
void* s21_memchr(const void* src, int char_to_search, s21_size_t length);
void* s21_memcpy(void* destination, const void* source,
                 s21_size_t number_of_bites_to_copy);
char* s21_strncat(char* destination, const char* source,
                  s21_size_t number_of_bytes);
int s21_strncmp(const char* str1, const char* str2, s21_size_t number_of_bytes);
s21_size_t s21_strcspn(const char* str1, const char* str2);

char* s21_strrchr(const char* str, int c);
char* s21_strchr(const char* str, int c);

char* s21_strtok(char* str, const char* delim);
char* s21_strstr(const char* haystack, const char* needle);

// Функции Валеры lambertm:
int s21_memcmp(const void* str1, const void* str2, s21_size_t n);
void* s21_memset(void* str, int c, s21_size_t n);
char* s21_strchr(const char* str, int c);
char* s21_strerror(int errnum);
char* s21_strpbrk(const char* str1, const char* str2);

// Lavernek
char* s21_strncpy(char* dest, const char* src, s21_size_t n);
void* s21_to_upper(const char* str);
void* s21_to_lower(const char* str);
void* s21_insert(const char* src, const char* str, s21_size_t start_index);
void* s21_trim(const char* src, const char* trim_chars);

void s21_trim_left(const char** src, const char* trim_chars,
                   s21_size_t* src_len, const s21_size_t trim_chars_len);
void s21_trim_right(const char** src, const char* trim_chars,
                    s21_size_t* src_len, const s21_size_t trim_chars_len);

// Функции и структуры для sprintf() (Nitaaldu)

typedef struct specificator {
  s21_size_t f_plus;      // флаг "плюс"
  s21_size_t f_minus;     // флаг "минус"
  s21_size_t f_space;     // флаг "пробел"
  s21_size_t f_hash;      // флаг "решетка"
  s21_size_t f_zero;      // флаг "ноль"
  s21_size_t f_accuracy;  // флаг "точность по умолчанию"
  s21_size_t width;       // ширина
  s21_size_t accuracy;    // точность
  s21_size_t len_type;  // длина: h - короткое, L/l- длинное
  s21_size_t symbol;    // символ спецификатора
  s21_size_t not_correct;  // признак корректности
} spec;

int s21_sprintf(char* str, const char* format, ...);

const char* parse_spec(const char* str, spec* curr_spec, va_list* args);
const char* parse_flags(const char* str, spec* curr_spec);
const char* parse_num(const char* str, s21_size_t* dst);
const char* parse_width(const char* str, spec* curr_spec, va_list* args);
const char* parse_accuracy(const char* str, spec* curr_spec, va_list* args);
const char* parse_length_type(const char* str, spec* curr_spec);
const char* parse_symbol(const char* str, spec* curr_spec);

char* spec_to_str(char* str, spec* curr_spec, va_list* args);

// Функции печати спецификаторов
#define BASE_8 8
#define BASE_10 10
#define BASE_16 16

// flags c, s
char* print_char(char* str, spec* curr_spec, va_list* args);
char* print_string(char* str, spec* curr_spec, va_list* args);

// flag d
char* print_int(char* str, spec* curr_spec, va_list* args);
void print_inv_buf_int(char* buffer, spec* curr_spec, long int value);
void decompose_sign_and_fillers_int(char* buffer_start, char* buffer_curr_pos,
                                    spec* curr_spec, s21_size_t counter,
                                    long int value);

// flags o,u,x,X
char* print_unsigned_int(char* str, spec* curr_spec, va_list* args);
void print_inv_buf_unsigned_int(char* buffer, spec* curr_spec, long int value,
                                int base);
void decompose_prefix_and_fillers_uint(char* buffer_start,
                                       char* buffer_curr_pos, spec* curr_spec,
                                       s21_size_t counter, long int value);
char* decompose_print_prefix_oct_and_hex(char* buffer, spec* curr_spec);

// flag f
char* print_float(char* str, spec* curr_spec, va_list* args);
s21_size_t decompose_print_float_nan(char* buffer, long double value);
s21_size_t decompose_print_float_inf(char* buffer, long double value);
s21_size_t decompose_print_float_abs_num(char* buffer, spec* curr_spec,
                                         long double value);
void decompose_sign_and_fillers_float(char* buffer_start, spec* curr_spec,
                                      s21_size_t counter, long double value);

// flag p
char* print_pointer(char* str, spec* curr_spec, va_list* args);
s21_size_t decompose_print_float_nil(char* buffer);

// calc_size
s21_size_t calc_size_int(spec* curr_spec, long int value);
s21_size_t calc_size_unsigned_int(spec* curr_spec, unsigned long int value,
                                  int base);
s21_size_t calc_size_float(spec* curr_spec, long double value);

// common and simple
s21_size_t decompose_print_inv_num(char* buffer, spec* curr_spec,
                                   long int value, int base);
char digit_to_symbol(int digit, int flag_uppercase);
char is_sign_int(spec* curr_spec, long int value);
char is_sign_float(spec* curr_spec, long double value);
long int inv_long_int(long int val);
void decompose_add_spaces(char* buffer, spec* curr_spec, s21_size_t counter);

#endif
