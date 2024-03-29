/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "test.check" instead.
 */

#include <check.h>

#include "my_SmartCalc.h"

START_TEST(ex_1) {
  char mistake[100];
  double result, x = 0;
  char cin[256] =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq_tol(-30.0721649, result, 7);
}
END_TEST

START_TEST(ex_2) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "(132+sin(asin(sqrt(ln(log(228.11)))))-4*5^6*(123))";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq_tol(-7687367.0737845, result, 7);
}
END_TEST

START_TEST(ex_3) {
  char mistake[100];
  double result, x = 0;
  char cin[256] =
      "sin(1)+cos(1)+asin(1)+acos(1)+atan(1)+tan(1)+sqrt(16)+ln(10)+log(10)";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq_tol(12.5979605, result, 7);
}
END_TEST

START_TEST(ex_4) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "1";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq(1, result);
}
END_TEST

START_TEST(ex_5) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "sin";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq(0, result);
}
END_TEST

START_TEST(ex_6) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "-sin(9-8)";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq_tol(-1.1884, result, 7);
}
END_TEST

START_TEST(ex_7) {
  char mistake[100];
  double result, x = 0;
  char cin[256] =
      "15mod(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq_tol(-39.0721649, result, 7);
}
END_TEST

START_TEST(ex_8) {
  char mistake[100];
  double result, x = 0;
  char cin[256] =
      "15m0d(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq(0, result);
}
END_TEST

START_TEST(ex_9) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "15/0";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq(0, result);
}
END_TEST

START_TEST(ex_10) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "15/0";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq(0, result);
}
END_TEST

START_TEST(ex_11) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "2--2";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_str_ge("Non-corrective input", mistake);
}
END_TEST

START_TEST(ex_12) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "2++2";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_str_ge("Non-corrective input", mistake);
}
END_TEST

START_TEST(ex_13) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "(1+2)(1+2)";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq(9, result);
}
END_TEST

START_TEST(ex_14) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "-(2^2)";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq(-4, result);
}
END_TEST

START_TEST(ex_15) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "-2^2";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq(-4, result);
}
END_TEST

START_TEST(ex_16) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "(2+3)*5";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq(25, result);
}
END_TEST

START_TEST(ex_17) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "1/2+(2+3)/(sin(9-2)^2-6/7)";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq_tol(-11.2506, result, 7);
}
END_TEST

START_TEST(ex_18) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "1/2)+(2.3.5+3)";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_str_ge("Non-corrective input", mistake);
}
END_TEST

START_TEST(ex_19) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "1/0";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_str_ge("Division by 0", mistake);
}
END_TEST

START_TEST(ex_20) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_str_ge("empty value", mistake);
}
END_TEST

START_TEST(ex_21) {
  char mistake[100];
  double result, x = 1;
  char cin[256] = "x";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq(1, result);
}
END_TEST

START_TEST(ex_22) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "sin()";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_str_ge("Non-corrective input", mistake);
}
END_TEST

START_TEST(ex_23) {
  char mistake[100];
  double result, x = 1;
  char cin[256] = "2^2^3";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_double_eq(256, result);
}
END_TEST

START_TEST(ex_24) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "/sin()";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_str_ge("Non-corrective input", mistake);
}
END_TEST

START_TEST(ex_25) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "x2";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_str_ge("Non-corrective input", mistake);
}
END_TEST

START_TEST(ex_26) {
  char mistake[100];
  double result, x = 0;
  char cin[256] = "2x";
  my_SmartCalc(cin, x, &result, mistake);
  ck_assert_str_ge("Non-corrective input", mistake);
}
END_TEST

START_TEST(ex_27) {
  double sum_vklada = 1000000;
  int period_vklada = 3;
  int count_v = 3;
  double perc_vklada = 10;
  int start_d = 28;
  int start_m = 12;
  int start_y = 2022;
  int flag_count_vklada = 2;
  int flag_in = 1;
  double sum_in = 10000;
  int period_in = 2;
  int in_day = 4;
  int in_mon = 1;
  int in_year = 2023;
  int flag_out = 1;
  double sum_out = 2000;
  int period_out = 2;
  int out_day = 8;
  int out_mon = 1;
  int out_year = 2023;
  double sum_tax = 0;
  double sum_perc = 0;
  double sum_balance_of_depos = 0;

  int capital = 0;
  int count_debits = 0;
  int count_vklada =
      countDays(count_v, start_d, start_m - 1, start_y, flag_count_vklada);
  debitStruct debits[count_vklada + 123];

  deposit(sum_vklada, period_vklada, count_vklada, perc_vklada, start_d,
          start_m - 1, start_y - 1900, flag_in, sum_in, period_in, in_day,
          in_mon - 1, in_year - 1900, flag_out, sum_out, period_out, out_day,
          out_mon - 1, out_year - 1900, capital, debits, &count_debits,
          &sum_perc, &sum_balance_of_depos);

  stractTax tax[debits[count_debits - 1].year - 2022];
  const double key_rate = 7.5;
  int count_tax = 0;
  tax_rent(debits, count_debits, key_rate, tax, &count_tax);
  ck_assert_double_eq_tol(322594.026499, sum_perc, 7);
  ck_assert_double_eq_tol(0.0000000, sum_tax, 7);
  ck_assert_double_eq_tol(322594.026499, sum_perc - sum_tax, 7);
  ck_assert_double_eq_tol(1144000.000000, sum_balance_of_depos, 7);
}
END_TEST

START_TEST(ex_28) {
  double sum = 100000;
  int perc = 10;
  double sum_perc = 0;
  double sum_sumPerc = 0;
  int count_mon = 24;
  int variant = 1;
  creditStruct credits[count_mon];
  credit(sum, count_mon, perc, credits, variant, &sum_perc, &sum_sumPerc);
  ck_assert_double_eq_tol(4614.49, credits[0].sum_pay, 7);
  ck_assert_double_eq_tol(10747.8, sum_perc, 7);
  ck_assert_double_eq_tol(110748, sum + sum_perc, 7);
}
END_TEST

START_TEST(ex_29) {
  double sum = 100000;
  int perc = 10;
  double sum_perc = 0;
  double sum_sumPerc = 0;
  int count_mon = 24;
  int variant = 2;
  creditStruct credits[count_mon];
  credit(sum, count_mon, perc, credits, variant, &sum_perc, &sum_sumPerc);
  ck_assert_double_eq_tol(5000, credits[0].sum_pay, 7);
  ck_assert_double_eq_tol(4201.39, credits[count_mon - 1].sum_pay, 7);
  ck_assert_double_eq_tol(110417, sum + sum_perc, 7);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, ex_1);
  tcase_add_test(tc1_1, ex_2);
  tcase_add_test(tc1_1, ex_3);
  tcase_add_test(tc1_1, ex_4);
  tcase_add_test(tc1_1, ex_5);
  tcase_add_test(tc1_1, ex_6);
  tcase_add_test(tc1_1, ex_7);
  tcase_add_test(tc1_1, ex_8);
  tcase_add_test(tc1_1, ex_9);
  tcase_add_test(tc1_1, ex_10);
  tcase_add_test(tc1_1, ex_11);
  tcase_add_test(tc1_1, ex_12);
  tcase_add_test(tc1_1, ex_13);
  tcase_add_test(tc1_1, ex_14);
  tcase_add_test(tc1_1, ex_15);
  tcase_add_test(tc1_1, ex_16);
  tcase_add_test(tc1_1, ex_17);
  tcase_add_test(tc1_1, ex_18);
  tcase_add_test(tc1_1, ex_19);
  tcase_add_test(tc1_1, ex_20);
  tcase_add_test(tc1_1, ex_21);
  tcase_add_test(tc1_1, ex_22);
  tcase_add_test(tc1_1, ex_23);
  tcase_add_test(tc1_1, ex_24);
  tcase_add_test(tc1_1, ex_25);
  tcase_add_test(tc1_1, ex_26);
  tcase_add_test(tc1_1, ex_27);
  tcase_add_test(tc1_1, ex_28);
  tcase_add_test(tc1_1, ex_29);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
