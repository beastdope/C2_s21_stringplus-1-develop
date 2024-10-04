#include "s21_string_tests.h"

START_TEST(test_s21_trim_1) {
  char *result = {0};
  result = s21_trim("123abc456xyz789", "123456789");
  if (result) {
    ck_assert_str_eq(result, "abc456xyz");
  }
  free(result);
}
END_TEST

START_TEST(test_s21_trim_2) {
  char *result = s21_trim("miu miu miu miu", " mui");
  if (result) {
    ck_assert_str_eq(result, "");
    free(result);
  }
}
END_TEST

START_TEST(test_s21_trim_3) {
  char *result = s21_trim("__aa  ", "a ");
  if (result) {
    ck_assert_str_eq(result, "__");
    free(result);
  }
}
END_TEST

START_TEST(test_s21_trim_4) {
  char *result = s21_trim("", "");
  if (result) {
    ck_assert_str_eq(result, "");
    free(result);
  }
}
END_TEST

START_TEST(test_s21_trim_5) {
  char *result = s21_trim("aa__aa", "a");
  if (result) {
    ck_assert_str_eq(result, "__");
    free(result);
  }
}
END_TEST

START_TEST(test_s21_trim_6) {
  char *result = s21_trim("abcdef", "acd");
  if (result) {
    ck_assert_str_eq(result, "bcdef");
    free(result);
  }
}
END_TEST

Suite *test_s21_trim(void) {
  Suite *s = suite_create("\033[42m-=S21_TRIM=-\033[0m");
  TCase *tc = tcase_create("s21_trim_tc");

  tcase_add_test(tc, test_s21_trim_1);
  tcase_add_test(tc, test_s21_trim_2);
  tcase_add_test(tc, test_s21_trim_3);
  tcase_add_test(tc, test_s21_trim_4);
  tcase_add_test(tc, test_s21_trim_5);
  tcase_add_test(tc, test_s21_trim_6);

  suite_add_tcase(s, tc);
  return s;
}