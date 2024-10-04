#include "s21_string_tests.h"

START_TEST(test_s21_to_upper_1) {
  char str1[] =
      "depeche mode are an english electronic music band formed in basildon, "
      "essex in 1980";
  char *str = s21_to_upper(str1);
  if (str) {
    ck_assert_str_eq(str,
                     "DEPECHE MODE ARE AN ENGLISH ELECTRONIC MUSIC BAND FORMED "
                     "IN BASILDON, ESSEX IN 1980");
    free(str);
  }
}
END_TEST

START_TEST(test_s21_to_upper_2) {
  char str1[] = "  maythe4th  ";
  char *str = s21_to_upper(str1);
  if (str) {
    ck_assert_str_eq(str, "  MAYTHE4TH  ");
    free(str);
  }
}
END_TEST

START_TEST(test_s21_to_upper_3) {
  char str1[] = "";
  char *str = s21_to_upper(str1);
  if (str) {
    ck_assert_str_eq(str, "");
    free(str);
  }
}
END_TEST

START_TEST(test_s21_to_upper_4) {
  char str1[] = "a";
  char *str = s21_to_upper(str1);
  if (str) {
    ck_assert_str_eq(str, "A");
    free(str);
  }
}
END_TEST

START_TEST(test_s21_to_upper_5) {
  char str1[] = " // // \\ ";
  char *str = s21_to_upper(str1);
  if (str) {
    ck_assert_str_eq(str, " // // \\ ");
    free(str);
  }
}
END_TEST

START_TEST(test_s21_to_upper_6) {
  char str1[] = "  __mOp";
  char *str = s21_to_upper(str1);
  if (str) {
    ck_assert_str_eq(str, "  __MOP");
    free(str);
  }
}
END_TEST

Suite *test_s21_to_upper(void) {
  Suite *s = suite_create("\033[42m-=S21_TO_UPPER=-\033[0m");
  TCase *tc = tcase_create("s21_to_upper_tc");

  tcase_add_test(tc, test_s21_to_upper_1);
  tcase_add_test(tc, test_s21_to_upper_2);
  tcase_add_test(tc, test_s21_to_upper_3);
  tcase_add_test(tc, test_s21_to_upper_4);
  tcase_add_test(tc, test_s21_to_upper_5);
  tcase_add_test(tc, test_s21_to_upper_6);

  suite_add_tcase(s, tc);
  return s;
}