#include "s21_string_tests.h"

START_TEST(strncpy_test_1) {
  char str_1[15] = "Hello, world!";
  char str_2[] = "Good";
  s21_size_t n = 4;
  ck_assert_str_eq(strncpy(str_1, str_2, n), s21_strncpy(str_1, str_2, n));
}
END_TEST

START_TEST(strncpy_test_2) {
  char str_1[15] = "Hello, world!";
  char str_2[] = "\0";
  s21_size_t n = 1;
  ck_assert_str_eq(strncpy(str_1, str_2, n), s21_strncpy(str_1, str_2, n));
}
END_TEST

START_TEST(strncpy_test_3) {
  char str_1[20] = "Hello, world!";
  char str_2[] = "\n";
  s21_size_t n = 1;
  ck_assert_str_eq(strncpy(str_1, str_2, n), s21_strncpy(str_1, str_2, n));
}
END_TEST

START_TEST(strncpy_test_4) {
  char str_1[20] = "Hello, world!";
  char str_2[] = "LOL";
  s21_size_t n = 3;
  ck_assert_str_eq(strncpy(str_1, str_2, n), s21_strncpy(str_1, str_2, n));
}
END_TEST

START_TEST(strncpy_test_5) {
  char str_1[20] = "Hello, world!";
  char str_2[] = " ";
  s21_size_t n = 1;
  ck_assert_str_eq(strncpy(str_1, str_2, n), s21_strncpy(str_1, str_2, n));
}
END_TEST

START_TEST(strncpy_test_6) {
  char str_1[20] = "lyulya";
  char str_2[] = "kebab";
  s21_size_t n = 2;
  ck_assert_str_eq(strncpy(str_1, str_2, n), s21_strncpy(str_1, str_2, n));
}
END_TEST

Suite *test_s21_strncpy(void) {
  Suite *s = suite_create("\033[42m-=S21_STRNCPY=-\033[0m");
  TCase *tc = tcase_create("s21_strncpy_tc");

  tcase_add_test(tc, strncpy_test_1);
  tcase_add_test(tc, strncpy_test_2);
  tcase_add_test(tc, strncpy_test_3);
  tcase_add_test(tc, strncpy_test_4);
  tcase_add_test(tc, strncpy_test_5);
  tcase_add_test(tc, strncpy_test_6);

  suite_add_tcase(s, tc);
  return s;
}