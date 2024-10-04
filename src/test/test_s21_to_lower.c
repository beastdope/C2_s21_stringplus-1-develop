#include "s21_string_tests.h"

START_TEST(test_s21_to_lower_1) {
  char str1[] =
      "DEPECHE MODE ARE an ENGLISH ELECTRONIC MUSIC BAND FOrMED IN "
      "BASILDON, ESSEX IN 1980";
  char *str = s21_to_lower(str1);
  if (str) {
    ck_assert_str_eq(str,
                     "depeche mode are an english electronic music band "
                     "formed in basildon, essex in 1980");
    free(str);
  }
}
END_TEST

START_TEST(test_s21_to_lower_2) {
  char str1[] = "  MAYTHE4TH  ";
  char *str = s21_to_lower(str1);
  if (str) {
    ck_assert_str_eq(str, "  maythe4th  ");
    free(str);
  }
}
END_TEST

START_TEST(test_s21_to_lower_3) {
  char str1[] = "";
  char *str = s21_to_lower(str1);
  if (str) {
    ck_assert_str_eq(str, "");
    free(str);
  }
}
END_TEST

START_TEST(test_s21_to_lower_4) {
  char str1[] = "A";
  char *str = s21_to_lower(str1);
  if (str) {
    ck_assert_str_eq(str, "a");
    free(str);
  }
}
END_TEST

START_TEST(test_s21_to_lower_5) {
  char str1[] = " // // \\ ";
  char *str = s21_to_lower(str1);
  if (str) {
    ck_assert_str_eq(str, " // // \\ ");
    free(str);
  }
}
END_TEST

START_TEST(test_s21_to_lower_6) {
  char str1[] = "  __MoP";
  char *str = s21_to_lower(str1);
  if (str) {
    ck_assert_str_eq(str, "  __mop");
    free(str);
  }
}
END_TEST

Suite *test_s21_to_lower(void) {
  Suite *s = suite_create("\033[42m-=S21_TO_LOWER=-\033[0m");
  TCase *tc = tcase_create("s21_to_lower_tc");

  tcase_add_test(tc, test_s21_to_lower_1);
  tcase_add_test(tc, test_s21_to_lower_2);
  tcase_add_test(tc, test_s21_to_lower_3);
  tcase_add_test(tc, test_s21_to_lower_4);
  tcase_add_test(tc, test_s21_to_lower_5);
  tcase_add_test(tc, test_s21_to_lower_6);

  suite_add_tcase(s, tc);
  return s;
}