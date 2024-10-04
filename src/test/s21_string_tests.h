#ifndef S21_STRING_TESTS_H
#define S21_STRING_TESTS_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

Suite *test_s21_strncpy(void);
Suite *test_s21_to_upper(void);
Suite *test_s21_to_lower(void);
Suite *test_s21_insert(void);
Suite *test_s21_trim(void);
Suite *test_s21_sprintf(void);

#endif