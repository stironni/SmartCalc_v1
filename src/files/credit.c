//
// Created by stironni on 13.12.2022.
//
#include "my_SmartCalc.h"

int credit(int sum, int count, int perc, creditStruct *credits, int variant,
           double *sum_perc, double *sum_sumPerc) {
  double sum_pay =
      sum *
      ((double)perc / 12 / 100 * pow((1 + (double)perc / 12 / 100), count)) /
      (pow((1 + (double)perc / 12 / 100), count) - 1);
  double sum2 = (double)sum;
  struct tm *u;
  const time_t timer = time(NULL);
  u = localtime(&timer);
  for (int i = 0; i < count; i++) {
    credits[i].pay_of_precent = sum2 * (double)perc / 12 / 100;
    if (variant == 1) {
      credits[i].sum_pay = sum_pay;
      credits[i].pay_of_main_credit =
          credits[i].sum_pay - credits[i].pay_of_precent;
      credits[i].balance_of_debt = sum2 - credits[i].pay_of_main_credit;
      sum2 = credits[i].balance_of_debt;
      *sum_perc = *sum_perc + credits[i].pay_of_precent;
    }
    if (variant == 2) {
      credits[i].pay_of_main_credit = (double)sum / count;
      credits[i].sum_pay =
          credits[i].pay_of_main_credit + credits[i].pay_of_precent;
      credits[i].balance_of_debt =
          sum - credits[i].pay_of_main_credit * (i + 1);
      sum2 = credits[i].balance_of_debt;
      *sum_perc = *sum_perc + credits[i].pay_of_precent;
    }
    time_t next = mktime(u);
    u = localtime(&next);
    months(u->tm_mon + 1, i, credits);
    credits[i].year = u->tm_year + 1900;
    u->tm_mon += 1;
  }
  *sum_sumPerc = sum + *sum_perc;
  roundNum(count, credits, &*sum_perc, &*sum_sumPerc);
  return 0;
}

void months(int mon, int i, creditStruct *credits) {
  char months[12][32] = {"January",   "February", "Mart",     "April",
                         "May",       "June",     "July",     "August",
                         "September", "October",  "November", "December"};
  int j = 1;
  while (j <= mon) {
    if (j == mon) {
      strcpy(credits[i].mon, months[j - 1]);
      j++;
    } else {
      j++;
    }
  }
}

int roundNum(int count, creditStruct *credits, double *sum_perc,
             double *sum_sumPerc) {
  for (int i = 0; i < count; i++) {
    credits[i].sum_pay = round(credits[i].sum_pay * 100) / 100;
    credits[i].pay_of_precent = round(credits[i].pay_of_precent * 100) / 100;
    credits[i].pay_of_main_credit =
        round(credits[i].pay_of_main_credit * 100) / 100;
    credits[i].balance_of_debt = round(credits[i].balance_of_debt * 100) / 100;
  }
  *sum_perc = round(*sum_perc * 100) / 100;
  *sum_sumPerc = round(*sum_sumPerc * 100) / 100;
  return 0;
}
