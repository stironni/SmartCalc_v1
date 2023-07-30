//
// Created by stironni on 13.12.2022.
//

#include <string.h>

#include "my_SmartCalc.h"

int countDays(int count_vklada, int start_d, int start_m, int start_y,
              int flag_count_vklada) {
  int return_flag = 0;
  struct tm u, count;
  time_t date_u, date_count;
  get_date(start_d, start_m, start_y, &u, &date_u);
  if (flag_count_vklada == 0) return_flag = count_vklada;
  if (flag_count_vklada == 1) {
    get_date(u.tm_mday, u.tm_mon + count_vklada, u.tm_year, &count,
             &date_count);
    return_flag = difftime(date_count, date_u) / (24 * 60 * 60);
  }
  if (flag_count_vklada == 2) {
    get_date(u.tm_mday, u.tm_mon, u.tm_year + count_vklada, &count,
             &date_count);
    return_flag = difftime(date_count, date_u) / (24 * 60 * 60);
  }
  return return_flag;
}

void deposit(double sum_vklada, int period_vklada, int count_vklada,
             double perc_vklada, int start_d, int start_m, int start_y,
             int flag_in, double sum_in, int period_in, int in_day, int in_mon,
             int in_year, int flag_out, double sum_out, int period_out,
             int out_day, int out_mon, int out_year, int capital,
             debitStruct *debits, int *count_debits, double *sum_perc,
             double *sum_balance_of_depos) {
  struct tm u, in, out;
  time_t date_u, date_in, date_out;
  double sum2 = sum_vklada;
  get_date(start_d, start_m, start_y, &u, &date_u);
  get_date(in_day, in_mon, in_year, &in, &date_in);
  get_date(out_day, out_mon, out_year, &out, &date_out);
  double sum_in_out = 0;
  int period = 0;
  double sum_period = 0;
  double perc_sum = 0;
  int j_count = 0;
  obnulDebit(count_vklada + 123, debits);
  debits[*count_debits].year = u.tm_year + 1900;
  debits[*count_debits].day = u.tm_mday;
  months_debit(u.tm_mon, 0, debits);
  debits[*count_debits].percent = 0;
  debits[*count_debits].deposit_replenished = sum_vklada;
  debits[*count_debits].balance_of_depos = sum_vklada;
  *count_debits += 1;
  // date in or/and date out like date start
  if (flag_in == 1 && date_in <= date_u) {
    if (period_in == 0) flag_in = 0;
    period_in_out(period_in, &in, &date_in);
  }
  if (flag_out == 1 && date_out <= date_u) {
    if (period_out == 0) flag_out = 0;
    period_in_out(period_out, &out, &date_out);
  }
  // main
  for (int i = 0; i < count_vklada; i = i + period) {
    sum_in_out = 0;
    sum_period = 0;
    period = frequency_of_payments(period_vklada, u, date_u, count_vklada);
    if (i + period < count_vklada)
      j_count = period;
    else
      j_count = count_vklada - i;
    get_date(u.tm_mday + 1, u.tm_mon, u.tm_year, &u, &date_u);
    for (int j = 0; j < j_count; j++) {
      if (flag_out == 1 || flag_in == 1)
        sum_in_out =
            in_out_pay(u, debits, *&count_debits, sum_in, &in, &date_in,
                       period_in, flag_in, sum_out, &out, &date_out, period_out,
                       flag_out);  // in / out deposit
      if (sum_in_out != 0) {
        sum2 = debits[*count_debits - 2].balance_of_depos;
        sum_in_out = 0;
      } else
        sum2 = debits[*count_debits - 1].balance_of_depos;
      sum_period = sum_period + (perc_sum + sum2) *
                                    ((double)perc_vklada / 100) /
                                    (365 + leap_year(u.tm_year));
      get_date(u.tm_mday + 1, u.tm_mon, u.tm_year, &u, &date_u);
    }
    get_date(u.tm_mday - 1, u.tm_mon, u.tm_year, &u, &date_u);
    debits[*count_debits].percent = sum_period;
    debits[*count_debits].year = u.tm_year + 1900;
    debits[*count_debits].day = u.tm_mday;
    months_debit(u.tm_mon, *count_debits, debits);
    debits[*count_debits].mon_number = u.tm_mon;
    if (capital == 1)
      debits[*count_debits].balance_of_depos =
          debits[*count_debits - 1].balance_of_depos +
          debits[*count_debits].percent;
    else
      debits[*count_debits].balance_of_depos =
          debits[*count_debits - 1].balance_of_depos;
    if (capital == 1)
      debits[*count_debits].deposit_replenished = debits[*count_debits].percent;
    else
      debits[*count_debits].deposit_replenished = 0;
    *count_debits = *count_debits + 1;
  }

  roundNum_dep(*count_debits, debits);
  *sum_balance_of_depos = debits[*count_debits - 1].balance_of_depos;
  for (int k = 0; k < *count_debits; k++)
    *sum_perc = *sum_perc + debits[k].percent;
}

void tax_rent(debitStruct *debits, int count_debits, double key_rate,
              stractTax *tax, int *count_tax) {
  double sum_perc_year = 0;

  for (int i = 2023; i <= debits[count_debits - 1].year; i++) {
    sum_perc_year = 0;
    for (int k = 0; k < count_debits; k++) {
      if (debits[k].year == i) {
        sum_perc_year = sum_perc_year + debits[k].percent;
      }
    }
    if (sum_perc_year > 1000000 * ((double)key_rate / 100)) {
      tax[*count_tax].year = i;
      tax[*count_tax].tax_year =
          round((sum_perc_year - (1000000 * ((double)key_rate / 100))) * 0.13 *
                100) /
          100;
      *count_tax = *count_tax + 1;
    }
  }
}

int frequency_of_payments(int period_vklada, struct tm u, time_t date_u,
                          int count_vklada) {
  int return_flag = 0;
  if (period_vklada == 0)
    return_flag = count_vklada;
  else if (period_vklada == 1)
    return_flag = 1;
  else if (period_vklada == 2)
    return_flag = 7;
  else if (period_vklada > 2) {
    struct tm u2;
    time_t date_u2;
    if (period_vklada == 3)
      get_date(u.tm_mday, u.tm_mon + 1, u.tm_year, &u2, &date_u2);
    if (period_vklada == 4)
      get_date(u.tm_mday, u.tm_mon + 3, u.tm_year, &u2, &date_u2);
    if (period_vklada == 5)
      get_date(u.tm_mday, u.tm_mon + 6, u.tm_year, &u2, &date_u2);
    if (period_vklada == 6)
      get_date(u.tm_mday, u.tm_mon + 12, u.tm_year, &u2, &date_u2);
    return_flag = difftime(date_u2, date_u) / (24 * 60 * 60);
    if (return_flag > count_vklada) return_flag = count_vklada;
  }
  return return_flag;
}

int in_out_pay(struct tm u, debitStruct *debits, int *count_debits,
               double sum_in, struct tm *in, time_t *date_in, int period_in,
               int flag_in, double sum_out, struct tm *out, time_t *date_out,
               int period_out, int flag_out) {
  int flag_ret = 0;
  if (flag_in == 1 && flag_out == 1) {
    if (in->tm_mday == out->tm_mday && in->tm_mon == out->tm_mon &&
        in->tm_year == out->tm_year && u.tm_mday == out->tm_mday &&
        u.tm_mon == out->tm_mon && in->tm_year == out->tm_year) {
      if (sum_in > sum_out) {
        sum_in = sum_in - sum_out;
        flag_out = 0;
        period_in_out(period_out, &*out, &*date_out);
      } else if (sum_out > sum_in) {
        sum_out = sum_out - sum_in;
        flag_in = 0;
        if (debits[*count_debits - 1].balance_of_depos - sum_out < 0) {
          flag_out = 0;
          period_in_out(period_out, &*out, &*date_out);
        }
        period_in_out(period_in, &*in, &*date_in);
      } else if (sum_out == sum_in) {
        flag_in = 0;
        flag_out = 0;
        period_in_out(period_in, &*in, &*date_in);
        period_in_out(period_out, &*out, &*date_out);
      }
    }
  }
  if (flag_in == 1 || flag_out == 1) {
    if (u.tm_mday == in->tm_mday && u.tm_mon == in->tm_mon &&
        u.tm_year == in->tm_year && flag_in == 1) {
      debits[*count_debits].year = u.tm_year + 1900;
      debits[*count_debits].day = u.tm_mday;
      months_debit(u.tm_mon, *count_debits, debits);
      debits[*count_debits].mon_number = u.tm_mon;
      debits[*count_debits].percent = 0;
      debits[*count_debits].deposit_replenished = sum_in;
      debits[*count_debits].balance_of_depos =
          debits[*count_debits - 1].balance_of_depos + sum_in;
      period_in_out(period_in, &*in, &*date_in);
      flag_ret = sum_in;
    }
    if (u.tm_mday == out->tm_mday && u.tm_mon == out->tm_mon &&
        u.tm_year == out->tm_year && flag_out == 1 &&
        debits[*count_debits - 1].balance_of_depos - sum_out >= 0) {
      debits[*count_debits].year = u.tm_year + 1900;
      debits[*count_debits].day = u.tm_mday;
      months_debit(u.tm_mon, *count_debits, debits);
      debits[*count_debits].mon_number = u.tm_mon;
      debits[*count_debits].percent = 0;
      debits[*count_debits].deposit_replenished = sum_out * -1;
      debits[*count_debits].balance_of_depos =
          debits[*count_debits - 1].balance_of_depos - sum_out;
      period_in_out(period_out, &*out, &*date_out);
      flag_ret = sum_out * -1;
    } else if (u.tm_mday == out->tm_mday && u.tm_mon == out->tm_mon &&
               u.tm_year == out->tm_year && flag_out == 1 &&
               debits[*count_debits - 1].balance_of_depos - sum_out < 0)
      period_in_out(period_out, &*out, &*date_out);
  }
  if (flag_ret != 0) *count_debits += 1;
  return flag_ret;
}

void period_in_out(int period, struct tm *in_out, time_t *date_in_out) {
  if (period == 1)
    get_date(in_out->tm_mday, in_out->tm_mon + 1, in_out->tm_year, &*in_out,
             &*date_in_out);
  if (period == 2)
    get_date(in_out->tm_mday, in_out->tm_mon + 2, in_out->tm_year, &*in_out,
             &*date_in_out);
  if (period == 3)
    get_date(in_out->tm_mday, in_out->tm_mon + 3, in_out->tm_year, &*in_out,
             &*date_in_out);
  if (period == 4)
    get_date(in_out->tm_mday, in_out->tm_mon + 6, in_out->tm_year, &*in_out,
             &*date_in_out);
  if (period == 5)
    get_date(in_out->tm_mday, in_out->tm_mon + 12, in_out->tm_year, &*in_out,
             &*date_in_out);
}

void get_date(int day, int mon, int year, struct tm *date, time_t *date_t) {
  time_t now;
  time(&now);
  *date = *localtime(&now);
  date->tm_sec = 0;
  date->tm_min = 0;
  date->tm_hour = 0;
  date->tm_mday = day;
  date->tm_mon = mon;
  date->tm_year = year;
  if (date_t)
    *date_t = mktime(date);
  else
    mktime(date);
}

int leap_year(int year) {
  year += 1900;
  int return_flag = 0;
  if (year % 400 == 0)
    return_flag = 1;
  else if (year % 100 == 0)
    return_flag = 0;
  else if (year % 4 == 0)
    return_flag = 1;
  else
    return_flag = 0;
  return return_flag;
}

void months_debit(int mon, int count_debits, debitStruct *debits) {
  char months[12][32] = {"January",   "February", "Mart",     "April",
                         "May",       "June",     "July",     "August",
                         "September", "October",  "November", "December"};
  int j = 1;
  while (j <= mon + 1) {
    if (j == mon + 1) {
      strcpy(debits[count_debits].mon, months[j - 1]);
      j++;
    } else {
      j++;
    }
  }
}

int roundNum_dep(int count_debits, debitStruct *debits) {
  for (int i = 0; i < count_debits; i++) {
    debits[i].percent = round(debits[i].percent * 100) / 100;
    debits[i].deposit_replenished =
        round(debits[i].deposit_replenished * 100) / 100;
    debits[i].balance_of_depos = round(debits[i].balance_of_depos * 100) / 100;
  }
  return 0;
}

void obnulDebit(int count, debitStruct *debits) {
  for (int k = count; k >= 0; k--) {
    debits[k].day = 0;
    debits[k].mon[0] = '\0';
    debits[k].mon_number = 0;
    debits[k].year = 0;
    debits[k].balance_of_depos = 0;
    debits[k].percent = 0;
    debits[k].deposit_replenished = 0;
  }
}
