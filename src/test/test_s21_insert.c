#include "s21_string_tests.h"

START_TEST(test_s21_insert_1) {
  char *result = {0};
  result = s21_insert("Hello!", ", world", 5);
  if (result) {
    ck_assert_str_eq(result, "Hello, world!");
    free(result);
  }
}
END_TEST

START_TEST(test_s21_insert_2) {
  char *result = s21_insert("Hello!", ", world", 35);
  ck_assert(result == s21_NULL);
  free(result);
}
END_TEST

START_TEST(test_s21_insert_3) {
  char *result = s21_insert("", "", 0);
  if (result) {
    ck_assert_str_eq(result, "");
    free(result);
  }
}
END_TEST

START_TEST(test_s21_insert_4) {
  char *result = s21_insert("1", "2", 1);
  if (result) {
    ck_assert_str_eq(result, "12");
    free(result);
  }
}
END_TEST

START_TEST(test_s21_insert_5) {
  char *result = s21_insert("    ", "2", 2);
  if (result) {
    ck_assert_str_eq(result, "  2  ");
    free(result);
  }
}
END_TEST

START_TEST(test_s21_insert_6) {
  char *result = s21_insert("__Miu__", "_Miu", 5);
  if (result) {
    ck_assert_str_eq(result, "__Miu_Miu__");
    free(result);
  }
}
END_TEST

Suite *test_s21_insert(void) {
  Suite *s = suite_create("\033[42m-=S21_INSERT=-\033[0m");
  TCase *tc = tcase_create("s21_insert_tc");

  tcase_add_test(tc, test_s21_insert_1);
  tcase_add_test(tc, test_s21_insert_2);
  tcase_add_test(tc, test_s21_insert_3);
  tcase_add_test(tc, test_s21_insert_4);
  tcase_add_test(tc, test_s21_insert_5);
  tcase_add_test(tc, test_s21_insert_6);

  suite_add_tcase(s, tc);
  return s;
}