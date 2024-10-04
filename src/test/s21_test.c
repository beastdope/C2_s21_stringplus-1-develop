#include <check.h>
#include <string.h>

#include "../s21_string.h"
#include "s21_string_tests.h"

START_TEST(s21_strlen_testing) {
  char test_1[] = "Hello";
  char test_2[] = "5\0";
  char test_3[] = " ";
  char test_4[] = "";
  char test_5[] = "2";
  char test_6[] = "2\0123";
  char test_7[] = "2\0asd";
  // сравнивает int

  ck_assert_int_eq(s21_strlen(test_1), strlen(test_1));
  ck_assert_int_eq(s21_strlen(test_2), strlen(test_2));
  ck_assert_int_eq(s21_strlen(test_3), strlen(test_3));
  ck_assert_int_eq(s21_strlen(test_4), strlen(test_4));
  ck_assert_int_eq(s21_strlen(test_5), strlen(test_5));
  ck_assert_int_eq(s21_strlen(test_6), strlen(test_6));
  ck_assert_int_eq(s21_strlen(test_7), strlen(test_7));
}
END_TEST

START_TEST(s21_memchr_testing) {
  char test_1[] = "KateKeygen";
  char test_2 = 'e';
  char test_3 = 't';
  char test_4[] = "1553/\0";
  char test_5[] = "!";
  char test_6 = 'z';
  char test_7 = ' ';
  char test_8 = '^';
  char test_9 = '\0';
  char test_10[] = "";
  char test_11 = '8';

  // Это макросик из библиотеки Check который выполняет проверку на равенство
  // двух беззнаковых целых чисел. (unsigned long)
  ck_assert_uint_eq((unsigned long)s21_memchr(test_1, test_2, 10),
                    (unsigned long)memchr(test_1, test_2, 10));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_1, test_3, 10),
                    (unsigned long)memchr(test_1, test_3, 10));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_4, test_6, 7),
                    (unsigned long)memchr(test_4, test_6, 7));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_5, test_7, 1),
                    (unsigned long)memchr(test_5, test_7, 1));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_4, test_8, 7),
                    (unsigned long)memchr(test_4, test_8, 7));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_4, test_9, 7),
                    (unsigned long)memchr(test_4, test_9, 7));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_10, test_7, 1),
                    (unsigned long)memchr(test_10, test_7, 1));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_10, test_11, 1),
                    (unsigned long)memchr(test_10, test_11, 1));
}
END_TEST

// ck_assert_str_eq сравниваем две строки по типу (ожидаемый, фактический)
START_TEST(s21_memcpy_testing) {
  char test_1[256] = "Vengeful_Spirit";
  char test_2[256] = "  ";
  char test_3[256] = "1\4";
  char test_4[256] = " ?";
  char test_5[256] = "";
  char test_6[256] = "123";
  char test_7[256] = "123\123";
  char test_8[256] = " ";
  char test_9[256] = " ";
  char test_10[256] = "55";
  char test_11[256] = "55";

  ck_assert_str_eq(s21_memcpy(test_1, test_2, 2), memcpy(test_1, test_2, 2));
  ck_assert_str_eq(s21_memcpy(test_3, test_4, 2), memcpy(test_3, test_4, 2));
  ck_assert_str_eq(s21_memcpy(test_5, test_6, 3), memcpy(test_5, test_6, 3));
  ck_assert_str_eq(s21_memcpy(test_6, test_7, 4), memcpy(test_6, test_7, 4));
  ck_assert_str_eq(s21_memcpy(test_8, test_9, 1), memcpy(test_8, test_9, 1));
  ck_assert_str_eq(s21_memcpy(test_10, test_11, 1),
                   memcpy(test_10, test_11, 1));
}
END_TEST

START_TEST(s21_strncat_testing) {
  char test_1[24] = "Not";
  char test_2[24] = " Today";
  char test_3[2] = "0";
  char test_4[] = "";
  char test_5[24] = "ok";
  char test_6[24] = "chpok";
  char test_7[] = " not ok";
  char test_8[24] = "";
  char test_9[5] = "";
  char test_10[24] = "15";
  char test_11[24] = "15";
  // сравниваем две строки на соответствие
  ck_assert_str_eq(s21_strncat(test_1, test_2, 6), strncat(test_1, test_2, 6));
  ck_assert_str_eq(s21_strncat(test_3, test_4, 1), strncat(test_3, test_4, 1));
  ck_assert_str_eq(s21_strncat(test_5, test_6, 5), strncat(test_5, test_6, 5));
  ck_assert_str_eq(s21_strncat(test_7, test_8, 0), strncat(test_7, test_8, 0));
  ck_assert_str_eq(s21_strncat(test_8, test_9, 1), strncat(test_8, test_9, 1));
  ck_assert_str_eq(s21_strncat(test_10, test_11, 2),
                   strncat(test_10, test_11, 2));
}
END_TEST

START_TEST(s21_memcmp_testing) {  // lambertm
  char test_1[] = "Hello";
  char test_2[] = "Hallo";
  char test_3[] = "hellq";
  char test_4[] = "heklo";
  char test_5[] = "Hello";
  char test_6[] = "qwerty";

  ck_assert_int_eq(s21_memcmp(test_1, test_2, 2), memcmp(test_1, test_2, 2));
  ck_assert_int_eq(s21_memcmp(test_1, test_3, 5), memcmp(test_1, test_3, 5));
  ck_assert_int_eq(s21_memcmp(test_1, test_4, 5), memcmp(test_1, test_4, 5));
  ck_assert_int_eq(s21_memcmp(test_1, test_5, 5), memcmp(test_1, test_5, 5));
  ck_assert_int_eq(s21_memcmp(test_1, test_6, 5), memcmp(test_1, test_6, 5));
  ck_assert_int_eq(s21_memcmp(test_2, test_2, 5), memcmp(test_2, test_2, 5));
  ck_assert_int_eq(s21_memcmp(test_5, test_2, 3), memcmp(test_5, test_2, 3));
}
END_TEST

START_TEST(s21_strncmp_testing) {
  char str1[] = "Ok it's 5";
  char str2[] = "Ok it's 5";
  char str3[] = "Ok\0";
  char str4[] = "";
  char str5[] = "";
  char str6[] = "o";
  char str7[] = "ok";

  ck_assert_int_eq(s21_strncmp(str1, str2, 9), strncmp(str1, str2, 9));
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
  ck_assert_int_eq(s21_strncmp(str1, str3, 3) > 0, strncmp(str1, str3, 3) > 0);
  ck_assert_int_eq(s21_strncmp(str4, str5, 1), strncmp(str4, str5, 1));
  ck_assert_int_eq(s21_strncmp(str6, str7, 2) < 0, strncmp(str6, str7, 2) < 0);
}
END_TEST

// ck_assert_str_eq сравниваем две строки по типу (ожидаемый, фактический)
START_TEST(s21_memset_testing) {  // lambertm
  char test_1[256] = "Very_long my-string90";
  char test_2[256] = " ";
  char test_3[256] = "1";
  char test_4[256] = " ?";
  char test_5[256] = "";
  char test_6[256] = "123123123123987654321x";
  char test_7[256] = "123\123";
  char test_8[256] = ".";
  char test_9[256] = "x";
  char test_10[256] = "55";
  char test_11 = '^';
  char test_12 = '\0';
  char test_13 = '0';
  char test_14[] = "";
  char test_15 = ' ';

  ck_assert_str_eq(s21_memset(test_1, -100, 5), memset(test_1, -100, 5));
  ck_assert_str_eq(s21_memset(test_1, 33, 2), memset(test_1, 33, 2));
  ck_assert_str_eq(s21_memset(test_1, -1, 3), memset(test_1, -1, 3));
  ck_assert_str_eq(s21_memset(test_1, 1, 4), memset(test_1, 1, 4));
  ck_assert_str_eq(s21_memset(test_1, 0, 1), memset(test_1, 0, 1));
  ck_assert_str_eq(s21_memset(test_10, 5, 1), memset(test_10, 5, 1));
  ck_assert_str_eq(s21_memset(test_7, 6, 6), memset(test_7, 6, 6));
  ck_assert_str_eq(s21_memset(test_10, 789, 2), memset(test_10, 789, 2));
  ck_assert_str_eq(s21_memset(test_2, -100, 5), memset(test_2, -100, 5));
  ck_assert_str_eq(s21_memset(test_3, 33, 2), memset(test_3, 33, 2));
  ck_assert_str_eq(s21_memset(test_4, -1, 3), memset(test_4, -1, 3));
  ck_assert_str_eq(s21_memset(test_5, 1, 4), memset(test_5, 1, 4));
  ck_assert_str_eq(s21_memset(test_6, 0, 1), memset(test_6, 0, 1));
  ck_assert_str_eq(s21_memset(test_8, 5, 1), memset(test_8, 5, 1));
  ck_assert_str_eq(s21_memset(test_9, 9874, 6), memset(test_9, 9874, 6));
  ck_assert_str_eq(s21_memset(test_1, test_11, 1), memset(test_1, test_11, 1));
  ck_assert_str_eq(s21_memset(test_1, test_12, 6), memset(test_1, test_12, 6));
  ck_assert_str_eq(s21_memset(test_1, test_13, 6), memset(test_1, test_13, 6));
  ck_assert_str_eq(s21_memset(test_14, test_15, 6),
                   memset(test_14, test_15, 6));
  ck_assert_str_eq(s21_memset(test_1, test_15, 6), memset(test_1, test_15, 6));
}
END_TEST

START_TEST(s21_strcspn_testing) {
  char test_1[] = "BoleanHere";
  char test_2[] = "Bolean";
  char test_3[] = "Figma here";
  char test_4[] = "figma";
  char test_5[] = "5/";
  char test_6[] = "?/";
  char test_7[] = " ";
  char test_8[] = "0123456789";
  char test_9[] = "0";
  char test_10[] = "1";
  ck_assert_uint_eq(s21_strcspn(test_1, test_2), strcspn(test_1, test_2));
  ck_assert_uint_eq(s21_strcspn(test_3, test_4), strcspn(test_3, test_4));
  ck_assert_uint_eq(s21_strcspn(test_3, test_5), strcspn(test_3, test_5));
  ck_assert_uint_eq(s21_strcspn(test_3, test_6), strcspn(test_3, test_6));
  ck_assert_uint_eq(s21_strcspn(test_3, test_7), strcspn(test_3, test_7));
  ck_assert_uint_eq(s21_strcspn(test_4, test_8), strcspn(test_4, test_8));
  ck_assert_uint_eq(s21_strcspn(test_2, test_7), strcspn(test_2, test_7));
  ck_assert_uint_eq(s21_strcspn(test_8, test_9), strcspn(test_8, test_9));
  ck_assert_uint_eq(s21_strcspn(test_8, test_10), strcspn(test_8, test_10));
}
END_TEST

START_TEST(s21_strrchr_testing) {
  char test1[] = "12312455654 123455654 9 1";
  char test2[] = ";lk, ;lk, ;lkdaq, l;kqwe";
  char test3[] = " ? ? ; ! № ; № !";
  char test4[] = "?";

  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, '1'),
                    (unsigned long)strrchr(test1, '1'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test1, ' '),
                    (unsigned long)strrchr(test1, ' '));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test2, 'b'),
                    (unsigned long)strrchr(test2, 'b'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test3, '?'),
                    (unsigned long)strrchr(test3, '?'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test3, ' '),
                    (unsigned long)strrchr(test3, ' '));
  ck_assert_str_eq(s21_strrchr(test2, '\0'), strrchr(test2, '\0'));
  ck_assert_uint_eq((unsigned long)s21_strrchr(test4, '?'),
                    (unsigned long)strrchr(test4, '?'));
}
END_TEST

START_TEST(s21_strpbrk_testing) {
  char test1[] = "Hi everyone!";
  char test2[] = "every";

  ck_assert_str_eq(s21_strpbrk(test1, test2), strpbrk(test1, test2));
  char test3[] = "9876543210";
  char test4[] = "5";
  char test5[] = "345";

  ck_assert_str_eq(s21_strpbrk(test3, test4), strpbrk(test3, test4));
  ck_assert_str_eq(s21_strpbrk(test3, test5), strpbrk(test3, test5));

  char *str = "This is the road to hell";
  char *empty = "";
  char *empty2 = "T";
  char *empty3 = "l";
  char *empty4 = "9123";

  ck_assert(s21_strpbrk(str, empty) == s21_NULL);
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str, empty),
                    (unsigned long)strpbrk(str, empty));
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str, empty2),
                    (unsigned long)strpbrk(str, empty2));
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str, empty3),
                    (unsigned long)strpbrk(str, empty3));
  ck_assert_uint_eq((unsigned long)s21_strpbrk(str, empty4),
                    (unsigned long)strpbrk(str, empty4));
}

END_TEST

START_TEST(s21_strchr_testing) {
  char str_1[] = "Coca-colastic";
  int symb_1 = 'a';
  char *chr_1 = s21_strchr(str_1, symb_1);
  ck_assert_str_eq(chr_1, "a-colastic");

  char str_2[] = "Coca-colastic";
  int symb_2 = 'a';
  char *chr_2 = strchr(str_2, symb_2);
  ck_assert_str_eq(chr_1, chr_2);
  ck_assert_str_eq(str_1, str_2);

  char str_3[] = "Keking";
  int symb_3 = '\0';
  char *chr_3 = s21_strchr(str_3, symb_3);

  char str_4[] = "Keking";
  int symb_4 = '\0';
  char *chr_4 = strchr(str_4, symb_4);

  // Сравниваем содержимое строк
  ck_assert_str_eq(chr_3, chr_4);
  ck_assert_str_eq(str_3, str_4);

  char str_5[] = "oium";
  int symb_5 = 'o';
  char *chr_5 = s21_strchr(str_5, symb_5);
  char str_6[] = "oium";
  int symb_6 = 'o';
  char *chr_6 = strchr(str_6, symb_6);
  ck_assert_str_eq(chr_5, chr_6);
  ck_assert_str_eq(str_5, str_6);

  char str_7[] = "gfdm";
  int symb_7 = 'g';
  char *chr_7 = s21_strchr(str_7, symb_7);
  char str_8[] = "gfdm";
  int symb_8 = 'g';
  char *chr_8 = strchr(str_8, symb_8);
  ck_assert_str_eq(chr_7, chr_8);
  ck_assert_str_eq(str_7, str_8);
}
END_TEST

START_TEST(s21_strtok_testing) {
  char str_strtok_1[] = "My-lil-nigga-gon-spit-some-shi";
  char delim_1[] = "-";

  char str_strtok_2[] = "My-lil-nigga-gon-spit-some-shi";
  char delim_2[] = "-";
  char *s42_strtok = s21_strtok(str_strtok_1, delim_1);
  char *origin_strtok = strtok(str_strtok_2, delim_2);
  while (s42_strtok != s21_NULL) {
    ck_assert_str_eq(s42_strtok, origin_strtok);
    s42_strtok = s21_strtok(s21_NULL, delim_1);
    origin_strtok = strtok(s21_NULL, delim_2);
  }
}
END_TEST

START_TEST(s21_strerror_testing) {  // lambertm
  char *case1 = s21_strerror(0);
  char *case2 = strerror(0);
  ck_assert_uint_eq((unsigned long)*case1, (unsigned long)*case2);

  char *case9 = s21_strerror(1);
  char *case10 = strerror(1);
  ck_assert_uint_eq((unsigned long)*case9, (unsigned long)*case10);

  char *case0 = s21_strerror(106);
  char *case3 = strerror(106);
  ck_assert_uint_eq((unsigned long)*case0, (unsigned long)*case3);

  char *case7 = s21_strerror(200);
  char *case8 = strerror(200);
  ck_assert_uint_eq((unsigned long)*case7, (unsigned long)*case8);

  char *case5 = s21_strerror(INT_MAX);
  char *case6 = strerror(INT_MAX);
  ck_assert_uint_eq((unsigned long)*case5, (unsigned long)*case6);

  char *case11 = s21_strerror(-1);
  char *case12 = strerror(-1);
  ck_assert_uint_eq((unsigned long)*case11, (unsigned long)*case12);
}
END_TEST

START_TEST(s21_strstr_testing) {
  char test_1[] = "Cambridge University";
  char test_2[] = "University";
  char test_3[] = "HolyMolyHolyDoly";
  char test_4[] = "Doly";
  char test_5[] = "1234";
  char test_6[] = "";
  char test_7[] = "6858432854432";
  char test_8[] = "432";
  char test_9[] = "5";
  char test_10[] = "6";
  char test_11[] = "Gh67812Ul";
  char test_12[] = "12qwer";
  char test_13[] = "1Gh";

  ck_assert_ptr_eq(s21_strstr(test_1, test_2), strstr(test_1, test_2));
  ck_assert_ptr_eq(s21_strstr(test_3, test_4), strstr(test_3, test_4));
  ck_assert_ptr_eq(s21_strstr(test_4, test_5), strstr(test_4, test_5));
  ck_assert_ptr_eq(s21_strstr(test_5, test_6), strstr(test_5, test_6));
  ck_assert_ptr_eq(s21_strstr(test_7, test_8), strstr(test_7, test_8));
  ck_assert_ptr_eq(s21_strstr(test_8, test_9), strstr(test_8, test_9));
  ck_assert_ptr_eq(s21_strstr(test_8, test_10), strstr(test_8, test_10));
  ck_assert_ptr_eq(s21_strstr(test_11, test_12), strstr(test_11, test_12));
  ck_assert_ptr_eq(s21_strstr(test_11, test_13), strstr(test_11, test_13));
}
END_TEST

Suite *s21_string_suite(void) {
  Suite *s1;
  TCase *tc_string_test;
  s1 = suite_create("s21_string");
  tc_string_test = tcase_create("String");
  tcase_add_test(tc_string_test, s21_strlen_testing);
  suite_add_tcase(s1, tc_string_test);
  return s1;
}

Suite *s21_memchr_suite(void) {
  Suite *s2;
  TCase *tc_memchr;
  s2 = suite_create("s21_memchr");
  tc_memchr = tcase_create("Memchr");
  tcase_add_test(tc_memchr, s21_memchr_testing);
  suite_add_tcase(s2, tc_memchr);
  return s2;
}

Suite *s21_memcpy_suite(void) {
  Suite *s3;
  TCase *tc_memcpy;
  s3 = suite_create("s21_memcpy");
  tc_memcpy = tcase_create("Memcpy");
  tcase_add_test(tc_memcpy, s21_memcpy_testing);
  suite_add_tcase(s3, tc_memcpy);
  return s3;
}

Suite *s21_strncat_suite(void) {
  Suite *s4;
  TCase *tc_strncat;
  s4 = suite_create("s21_strncat");
  tc_strncat = tcase_create("Strncat");
  tcase_add_test(tc_strncat, s21_strncat_testing);
  suite_add_tcase(s4, tc_strncat);
  return s4;
}

Suite *s21_memcmp_suite(void) {  // lambertm
  Suite *s20;
  TCase *tc_memcmp;
  s20 = suite_create("s21_memcmp");
  tc_memcmp = tcase_create("Memcmp");
  tcase_add_test(tc_memcmp, s21_memcmp_testing);
  suite_add_tcase(s20, tc_memcmp);
  return s20;
}

Suite *s21_memset_suite(void) {  // lambertm
  Suite *s21;
  TCase *tc_memset;
  s21 = suite_create("s21_memset");
  tc_memset = tcase_create("Memset");
  tcase_add_test(tc_memset, s21_memset_testing);
  suite_add_tcase(s21, tc_memset);
  return s21;
}

Suite *s21_strncmp_suite(void) {
  Suite *s5;
  TCase *tc_strncmp;
  s5 = suite_create("s21_strncmp");
  tc_strncmp = tcase_create("Strncmp");
  tcase_add_test(tc_strncmp, s21_strncmp_testing);
  suite_add_tcase(s5, tc_strncmp);
  return s5;
}
Suite *s21_strcspn_suite(void) {
  Suite *s6;
  TCase *tc_strcspn;
  s6 = suite_create("s21_strcspn");
  tc_strcspn = tcase_create("Strcspn");
  tcase_add_test(tc_strcspn, s21_strcspn_testing);
  suite_add_tcase(s6, tc_strcspn);
  return s6;
}

Suite *s21_strrchr_suite(void) {
  Suite *s7;
  TCase *tc_strrchr;
  s7 = suite_create("s21_strrchr");
  tc_strrchr = tcase_create("Strrchr");
  tcase_add_test(tc_strrchr, s21_strrchr_testing);
  suite_add_tcase(s7, tc_strrchr);
  return s7;
}

Suite *s21_strchr_suite(void) {
  Suite *s8;
  TCase *tc_strchr;
  s8 = suite_create("s21_strchr");
  tc_strchr = tcase_create("Strchr");
  tcase_add_test(tc_strchr, s21_strchr_testing);
  suite_add_tcase(s8, tc_strchr);
  return s8;
}

Suite *s21_strtok_suite(void) {
  Suite *s9;
  TCase *tc_strtok;
  s9 = suite_create("s21_strtok");
  tc_strtok = tcase_create("Strtok");
  tcase_add_test(tc_strtok, s21_strtok_testing);
  suite_add_tcase(s9, tc_strtok);
  return s9;
}

Suite *s21_strerror_suite(void) {  // lambertm
  Suite *s22;
  TCase *tc_strerror;
  s22 = suite_create("s21_strerror");
  tc_strerror = tcase_create("Strerror");
  tcase_add_test(tc_strerror, s21_strerror_testing);
  suite_add_tcase(s22, tc_strerror);
  return s22;
}

Suite *s21_strpbrk_suite(void) {  // lambertm
  Suite *s23;
  TCase *tc_strpbrk;
  s23 = suite_create("s21_strpbrk");
  tc_strpbrk = tcase_create("Strpbrk");
  tcase_add_test(tc_strpbrk, s21_strpbrk_testing);
  suite_add_tcase(s23, tc_strpbrk);
  return s23;
}

Suite *s21_strstr_suite(void) {
  Suite *s10;
  TCase *tc_strstr;
  s10 = suite_create("s21_strstr");
  tc_strstr = tcase_create("strstr");
  tcase_add_test(tc_strstr, s21_strstr_testing);
  suite_add_tcase(s10, tc_strstr);
  return s10;
}

int main(void) {
  int failed = 0;
  Suite *s21_string_tests[] = {test_s21_strncpy(),
                               test_s21_to_upper(),
                               test_s21_to_lower(),
                               test_s21_insert(),
                               test_s21_trim(),
                               test_s21_sprintf(),
                               NULL};
  for (int i = 0; s21_string_tests[i] != NULL; i++) {
    printf("\033[46m/start\033[0m ");
    SRunner *sr = srunner_create(s21_string_tests[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  // printf("========= FAILED: %d =========\n", failed);

  int numbers_failed;
  Suite *string;
  Suite *memchr;
  Suite *memcpy;
  Suite *strncat;

  Suite *memcmp;    // lambertm
  Suite *memset;    // lambertm
  Suite *strerror;  // lambertm
  Suite *strpbrk;   // lambertm

  Suite *strncmp;
  Suite *strcspn;
  Suite *strrchr;
  Suite *strchr;
  Suite *strtok;
  Suite *strstr;

  SRunner *sr_string;
  SRunner *sr_memchr;
  SRunner *sr_memcpy;
  SRunner *sr_strncat;

  SRunner *sr_memcmp;    // lambertm
  SRunner *sr_memset;    // lambertm
  SRunner *sr_strerror;  // lambertm
  SRunner *sr_strpbrk;   // lambertm

  SRunner *sr_strncmp;
  SRunner *sr_strcspn;
  SRunner *sr_strrchr;
  SRunner *sr_strchr;
  SRunner *sr_strtok;
  SRunner *sr_strstr;

  string = s21_string_suite();
  memchr = s21_memchr_suite();
  memcpy = s21_memcpy_suite();
  strncat = s21_strncat_suite();

  memcmp = s21_memcmp_suite();      // lambertm
  memset = s21_memset_suite();      // lambertm
  strerror = s21_strerror_suite();  // lambertm
  strpbrk = s21_strpbrk_suite();    // lambertm

  strncmp = s21_strncmp_suite();
  strcspn = s21_strcspn_suite();
  strrchr = s21_strrchr_suite();
  strchr = s21_strchr_suite();
  strtok = s21_strtok_suite();
  strstr = s21_strstr_suite();

  sr_string = srunner_create(string);
  srunner_run_all(sr_string, CK_NORMAL);
  numbers_failed = srunner_ntests_failed(sr_string);
  srunner_free(sr_string);

  sr_memchr = srunner_create(memchr);
  srunner_run_all(sr_memchr, CK_NORMAL);
  numbers_failed = srunner_ntests_failed(sr_memchr);
  srunner_free(sr_memchr);

  sr_memcpy = srunner_create(memcpy);
  srunner_run_all(sr_memcpy, CK_NORMAL);
  numbers_failed = srunner_ntests_failed(sr_memcpy);
  srunner_free(sr_memcpy);

  sr_strncat = srunner_create(strncat);
  srunner_run_all(sr_strncat, CK_NORMAL);
  numbers_failed = srunner_ntests_failed(sr_strncat);
  srunner_free(sr_strncat);

  sr_memcmp = srunner_create(memcmp);  // lambertm
  srunner_run_all(sr_memcmp, CK_NORMAL);
  numbers_failed = srunner_ntests_failed(sr_memcmp);
  srunner_free(sr_memcmp);

  sr_strncmp = srunner_create(strncmp);
  srunner_run_all(sr_strncmp, CK_NORMAL);
  numbers_failed = srunner_ntests_failed(sr_strncmp);
  srunner_free(sr_strncmp);

  sr_memset = srunner_create(memset);  //// lambertm
  srunner_run_all(sr_memset, CK_NORMAL);
  numbers_failed = srunner_ntests_failed(sr_memset);
  srunner_free(sr_memset);

  sr_strcspn = srunner_create(strcspn);
  srunner_run_all(sr_strcspn, CK_NORMAL);
  numbers_failed = srunner_ntests_failed(sr_strcspn);
  srunner_free(sr_strcspn);

  sr_strrchr = srunner_create(strrchr);
  srunner_run_all(sr_strrchr, CK_NORMAL);
  numbers_failed = srunner_ntests_failed(sr_strrchr);
  srunner_free(sr_strrchr);

  sr_strchr = srunner_create(strchr);
  srunner_run_all(sr_strchr, CK_NORMAL);
  numbers_failed = srunner_ntests_failed(sr_strchr);
  srunner_free(sr_strchr);

  sr_strtok = srunner_create(strtok);
  srunner_run_all(sr_strtok, CK_NORMAL);
  numbers_failed = srunner_ntests_failed(sr_strtok);
  srunner_free(sr_strtok);

  sr_strerror = srunner_create(strerror);  // lambertm
  srunner_run_all(sr_strerror, CK_NORMAL);
  numbers_failed = srunner_ntests_failed(sr_strerror);
  srunner_free(sr_strerror);

  sr_strpbrk = srunner_create(strpbrk);  // lambertm
  srunner_run_all(sr_strpbrk, CK_NORMAL);
  numbers_failed = srunner_ntests_failed(sr_strpbrk);
  srunner_free(sr_strpbrk);

  sr_strstr = srunner_create(strstr);
  srunner_run_all(sr_strstr, CK_NORMAL);
  numbers_failed = srunner_ntests_failed(sr_strstr);
  srunner_free(sr_strstr);

  numbers_failed += failed;
  return (numbers_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}