//
// Created by stironni on 9/15/22.
//

#ifndef C7_SMARTCALC_V1_0_0_CALC_H
#define C7_SMARTCALC_V1_0_0_CALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  char value[264];
  int priority;
  double num;
} Lexemes;

typedef struct {
  char mon[32];
  int year;
  double sum_pay;
  double pay_of_main_credit;
  double pay_of_precent;
  double balance_of_debt;
} creditStruct;

typedef struct {
  int day;
  int mon_number;
  char mon[32];
  int year;
  double percent;
  double deposit_replenished;
  double balance_of_depos;
} debitStruct;

typedef struct {
  int year;
  double tax_year;
} stractTax;

int my_SmartCalc(char *cin, double x, double *res, char *mistake_text);
int parser(char *cin, Lexemes *Lexeme, int *cnt_L, double x);
int OPN(int cnt_L, Lexemes *Lexeme, int *cnt_vs, Lexemes *vs, int cnt_stek,
        Lexemes *stek);
int calc(int cnt_vs, Lexemes *vs, double *res);
void obnul(int *cnt_stek, Lexemes *stek);
void add_to_stek_from_Lexeme(int k, Lexemes *Lexeme, int *cnt_stek,
                             Lexemes *stek);
void add_to_vs_from_Lexeme(int k, Lexemes *Lexeme, int *cnt_vs, Lexemes *vs);
void add_to_vs_from_stek(int cnt_stek, Lexemes *stek, int *cnt_vs, Lexemes *vs);
void add_to_vs_from_stek_one(int *cnt_stek, Lexemes *stek, int *cnt_vs,
                             Lexemes *vs);
void add_to_vs_stek_zero(int *cnt_vs_stek, Lexemes *vs_stek);
void free_stek_to_bracket(int *cnt_stek, Lexemes *stek, int *cnt_vs,
                          Lexemes *vs);
void priority_OPN(int *k, Lexemes *Lexeme, int *cnt_vs, Lexemes *vs,
                  int *cnt_stek, Lexemes *stek, int openFlag);
int credit(int sum, int count, int perc, creditStruct *credits, int variant,
           double *sum_perc, double *sum_sumPerc);
void months(int mon, int i, creditStruct *credits);
int roundNum(int count, creditStruct *credits, double *sum_perc,
             double *sum_sumPerc);
void months_debit(int mon, int count_debits, debitStruct *debits);
int leap_year(int year);
void get_date(int day, int mon, int year, struct tm *date, time_t *date_t);
int in_out_pay(struct tm u, debitStruct *debits, int *count_debits,
               double sum_in, struct tm *in, time_t *date_in, int period_in,
               int flag_in, double sum_out, struct tm *out, time_t *date_out,
               int period_out, int flag_out);
int countDays(int count_vklada, int start_d, int start_m, int start_y,
              int flag_count_vklada);
void deposit(double sum_v, int period_v, int count_day_v, double perc_v,
             int start_d, int start_m, int start_y, int flag_in, double sum_in,
             int period_in, int in_day, int in_mon, int in_year, int flag_out,
             double sum_out, int period_out, int out_day, int out_mon,
             int out_year, int capital, debitStruct *debits, int *count_debits,
             double *sum_perc, double *sum_balance_of_depos);
int frequency_of_payments(int flag_period, struct tm u, time_t date_u,
                          int count);
int roundNum_dep(int count_debits, debitStruct *debits);
void tax_rent(debitStruct *debits, int count_debits, double key_rate,
              stractTax *tax, int *count_tax);
void obnulDebit(int count, debitStruct *debits);
void period_in_out(int period, struct tm *in_out, time_t *date_in_out);
#endif  // C7_SMARTCALC_V1_0_0_CALC_H
