//
// Created by stironni on 9/15/22.
//

#include "my_SmartCalc.h"

int my_SmartCalc(char *cin, double x, double *result, char *mistake_text) {
  Lexemes Lexeme[256] = {0}, vs[256] = {0}, stek[256] = {0};
  int cnt_L = 0, cnt_vs = 0, cnt_stek = 0;
  double res = 0;
  int parser_res = 0, OPN_res = 0, calc_res = 0, ret_flag = 0;
  if (cin[0] == '\0') {
    ret_flag = 1;
    strcpy(mistake_text, "empty value");
  } else {
    parser_res = parser(cin, Lexeme, &cnt_L, x);
    if (parser_res == 0) {
      OPN_res = OPN(cnt_L, Lexeme, &cnt_vs, vs, cnt_stek, stek);
      if (OPN_res == 0) {
        calc_res = calc(cnt_vs, vs, &res);
        if (calc_res == 0) {
          *result = res;
          ret_flag = 0;
        } else {
          ret_flag = 1;
          *result = 0;
        }
      } else {
        ret_flag = 1;
        *result = 0;
      }
    } else {
      ret_flag = 1;
      *result = 0;
    }
  }

  if (parser_res == 1) {
    strcpy(mistake_text, "Non-corrective input");
  }
  if (calc_res == 3) {
    strcpy(mistake_text, "Division by 0");
  }
  if (OPN_res == 5) {
    strcpy(mistake_text, "Non-corrective input");
  }

  return ret_flag;
}

int parser(char *cin, Lexemes *Lexeme, int *cnt_L, double x) {
  char number[256] = {0};
  //  int count_number = 0;
  int ret_flag = 0;
  int cnt_open = 0, cnt_closed = 0;
  for (size_t i = 0; i < strlen(cin); i++) {
    switch (cin[i]) {
      case '+':
        if (strchr("-+*/m^", cin[i + 1])) ret_flag = 1;
        if ((strchr("(-+*/d^", cin[i - 1]) && i > 0 &&
             ((cin[i + 1] >= '0' && cin[i + 1] <= '9') ||
              strchr("scatl(x", cin[i + 1]))) ||
            i == 0) {
          strcpy(Lexeme[*cnt_L].value, "0");
          Lexeme[*cnt_L].priority = 7;
          Lexeme[*cnt_L].num = 0;
          *cnt_L += 1;
          Lexeme[*cnt_L].value[0] = '+';
          Lexeme[*cnt_L].priority = 5;
        } else {
          Lexeme[*cnt_L].value[0] = '+';
          Lexeme[*cnt_L].priority = 5;
        }
        break;
      case '-':
        if (strchr("-+*/m^", cin[i + 1])) ret_flag = 1;
        if ((strchr("(-+*/d^", cin[i - 1]) && i > 0 &&
             ((cin[i + 1] >= '0' && cin[i + 1] <= '9') ||
              strchr("scatl(x", cin[i + 1]))) ||
            i == 0) {
          strcpy(Lexeme[*cnt_L].value, "0");
          Lexeme[*cnt_L].priority = 7;
          Lexeme[*cnt_L].num = 0;
          *cnt_L += 1;
          Lexeme[*cnt_L].value[0] = '-';
          Lexeme[*cnt_L].priority = 5;
        } else {
          Lexeme[*cnt_L].value[0] = '-';
          Lexeme[*cnt_L].priority = 5;
        }
        break;
      case '/':
        if (strchr("-+*/m^", cin[i + 1])) ret_flag = 1;
        Lexeme[*cnt_L].value[0] = '/';
        Lexeme[*cnt_L].priority = 4;
        break;
      case '*':
        if (strchr("-+*/m^", cin[i + 1])) ret_flag = 1;
        Lexeme[*cnt_L].value[0] = '*';
        Lexeme[*cnt_L].priority = 4;
        break;
      case '^':
        if (strchr("-+*/m^", cin[i + 1])) ret_flag = 1;
        Lexeme[*cnt_L].value[0] = '^';
        Lexeme[*cnt_L].priority = 3;
        break;
      case 'x':
        Lexeme[*cnt_L].value[0] = 'x';
        Lexeme[*cnt_L].priority = 7;
        Lexeme[*cnt_L].num = x;
        break;
      case '(':
        if (strchr("*/m^", cin[i + 1])) ret_flag = 1;
        if (cin[i + 1] == ')') {
          ret_flag = 1;
        } else if (cin[i - 1] == ')') {
          Lexeme[*cnt_L].value[0] = '*';
          Lexeme[*cnt_L].priority = 4;
          *cnt_L += 1;
          Lexeme[*cnt_L].value[0] = '(';
          Lexeme[*cnt_L].priority = 1;
          cnt_open++;
        } else if (strchr("^/*m", cin[i + 1])) {
          ret_flag = 1;
        } else {
          Lexeme[*cnt_L].value[0] = '(';
          Lexeme[*cnt_L].priority = 1;
          cnt_open++;
        }
        break;
      case ')':
        Lexeme[*cnt_L].value[0] = ')';
        Lexeme[*cnt_L].priority = 1;
        cnt_closed++;
        if (cnt_closed > cnt_open) ret_flag = 1;
        break;
      case 'm':
        if (cin[i] == 'm' && cin[i + 1] == 'o' && cin[i + 2] == 'd') {
          if (strchr("-+*/m^", cin[i + 3]))
            ret_flag = 1;
          else {
            strcpy(Lexeme[*cnt_L].value, "%");
            Lexeme[*cnt_L].priority = 4;
            i += 2;
          }
        } else {
          ret_flag = 1;
        }
        break;
      default:
        if (cin[i] >= '0' && cin[i] <= '9') {
          memset(number, '\n', 256);
          //            number[0] = '\0';
          int j = 0;
          do {
            number[j] = cin[i];
            j++;
            i++;
          } while ((cin[i] >= '0' && cin[i] <= '9') || cin[i] == '.');
          if (number[j - 1] == '.') ret_flag = 1;
          strcpy(Lexeme[*cnt_L].value, number);
          Lexeme[*cnt_L].priority = 7;
          Lexeme[*cnt_L].num = atof(number);
          i--;
          //          count_number++;
        } else if (cin[i] == 'l' && cin[i + 1] == 'n' && cin[i + 2] == '(') {
          if (strchr("*/m^", cin[i + 3])) ret_flag = 1;
          strcpy(Lexeme[*cnt_L].value, "ln");
          Lexeme[*cnt_L].priority = 2;
          i++;
        } else if (cin[i] == 's' && cin[i + 1] == 'i' && cin[i + 2] == 'n' &&
                   cin[i + 3] == '(') {
          if (strchr("*/m^", cin[i + 4])) ret_flag = 1;
          strcpy(Lexeme[*cnt_L].value, "sin");
          Lexeme[*cnt_L].priority = 2;
          i += 2;
        } else if (cin[i] == 'c' && cin[i + 1] == 'o' && cin[i + 2] == 's' &&
                   cin[i + 3] == '(') {
          if (strchr("*/m^", cin[i + 4])) ret_flag = 1;
          strcpy(Lexeme[*cnt_L].value, "cos");
          Lexeme[*cnt_L].priority = 2;
          i += 2;
        } else if (cin[i] == 't' && cin[i + 1] == 'a' && cin[i + 2] == 'n' &&
                   cin[i + 3] == '(') {
          if (strchr("*/m^", cin[i + 4])) ret_flag = 1;
          strcpy(Lexeme[*cnt_L].value, "tan");
          Lexeme[*cnt_L].priority = 2;
          i += 2;
        } else if (cin[i] == 'l' && cin[i + 1] == 'o' && cin[i + 2] == 'g' &&
                   cin[i + 3] == '(') {
          if (strchr("*/m^", cin[i + 4])) ret_flag = 1;
          strcpy(Lexeme[*cnt_L].value, "log");
          Lexeme[*cnt_L].priority = 2;
          i += 2;
        } else if (cin[i] == 'a' && cin[i + 1] == 's' && cin[i + 2] == 'i' &&
                   cin[i + 3] == 'n' && cin[i + 4] == '(') {
          if (strchr("*/m^", cin[i + 5])) ret_flag = 1;
          strcpy(Lexeme[*cnt_L].value, "asin");
          Lexeme[*cnt_L].priority = 2;
          i += 3;
        } else if (cin[i] == 'a' && cin[i + 1] == 'c' && cin[i + 2] == 'o' &&
                   cin[i + 3] == 's' && cin[i + 4] == '(') {
          if (strchr("*/m^", cin[i + 5])) ret_flag = 1;
          strcpy(Lexeme[*cnt_L].value, "acos");
          Lexeme[*cnt_L].priority = 2;
          i += 3;
        } else if (cin[i] == 'a' && cin[i + 1] == 't' && cin[i + 2] == 'a' &&
                   cin[i + 3] == 'n' && cin[i + 4] == '(') {
          if (strchr("*/m^", cin[i + 5])) ret_flag = 1;
          strcpy(Lexeme[*cnt_L].value, "atan");
          Lexeme[*cnt_L].priority = 2;
          i += 3;
        } else if (cin[i] == 's' && cin[i + 1] == 'q' && cin[i + 2] == 'r' &&
                   cin[i + 3] == 't' && cin[i + 4] == '(') {
          if (strchr("*/m^", cin[i + 5])) ret_flag = 1;

          strcpy(Lexeme[*cnt_L].value, "sqrt");
          Lexeme[*cnt_L].priority = 2;
          i += 3;
        } else {
          ret_flag = 1;
        }
        break;
    }
    *cnt_L += 1;
  }
  if (cnt_open != cnt_closed) ret_flag = 1;
  if ((Lexeme[*cnt_L - 1].priority >= 3 && Lexeme[*cnt_L - 1].priority <= 5) ||
      (Lexeme[0].priority >= 3 && Lexeme[0].priority <= 5))
    ret_flag = 1;
  return ret_flag;
}

int OPN(int cnt_L, Lexemes *Lexeme, int *cnt_vs, Lexemes *vs, int cnt_stek,
        Lexemes *stek) {
  int ret_flag = 0;
  int openFlag = 0;
  obnul(&cnt_stek, stek);
  for (int k = 0; k < cnt_L; k++) {
    if (Lexeme[k].priority >= 2 && Lexeme[k].priority <= 6 &&
        Lexeme[k + 1].priority >= 3 && Lexeme[k + 1].priority <= 6)
      ret_flag = 5;
    switch (Lexeme[k].priority) {
      case 1:
        if (Lexeme[k].value[0] == '(') {
          add_to_stek_from_Lexeme(k, Lexeme, &cnt_stek, stek);
          openFlag++;
        }
        if (Lexeme[k].value[0] == ')' && openFlag > 0) {
          if (stek[cnt_stek - 1].value[0] == '(') {
            add_to_vs_stek_zero(&*cnt_vs, vs);
            vs[*cnt_vs].value[0] = '+';
            vs[*cnt_vs].priority = 5;
            vs[*cnt_vs].num = 0;
            *cnt_vs += 1;
            stek[cnt_stek - 1].value[0] = '\0';
            stek[cnt_stek - 1].priority = 0;
            stek[cnt_stek - 1].num = 0;
            cnt_stek--;
          } else {
            free_stek_to_bracket(&cnt_stek, stek, &*cnt_vs, vs);
          }
          openFlag--;
        }
        break;
      case 2:
        add_to_stek_from_Lexeme(k, Lexeme, &cnt_stek, stek);
        add_to_vs_stek_zero(&*cnt_vs, vs);
        break;
      case 6:  /// +/-
      case 3:  /// ^
      case 4:  /// * /
      case 5:  /// + -
        priority_OPN(&k, Lexeme, &*cnt_vs, vs, &cnt_stek, stek, openFlag);
        break;

      case 7:  /// numbers
        if ((Lexeme[k + 1].value[0] == '(') ||
            ((Lexeme[k - 1].priority == 7 || Lexeme[k + 1].priority == 7) &&
             strcmp(Lexeme[k].value, "x") == 0))
          ret_flag = 5;
        //        if (Lexeme[k + 1].value[0] == '(') ret_flag = 5;
        if (cnt_L == 1) {
          add_to_vs_from_Lexeme(k, Lexeme, &*cnt_vs, vs);
          add_to_vs_stek_zero(&*cnt_vs, vs);
          vs[*cnt_vs].value[0] = '+';
          vs[*cnt_vs].priority = 5;
          vs[*cnt_vs].num = 0;
          *cnt_vs += 1;
        } else {
          add_to_vs_from_Lexeme(k, Lexeme, &*cnt_vs, vs);
        }
        break;
    }
  }
  add_to_vs_from_stek(cnt_stek, stek, &*cnt_vs, vs);
  obnul(&cnt_stek, stek);
  return ret_flag;
}

int calc(int cnt_vs, Lexemes *vs, double *res) {
  int ret_flag = 0;
  while (cnt_vs != 1) {
    for (int s = 0; s < cnt_vs; s++) {
      if (vs[s - 2].priority == 7 && vs[s - 1].priority == 7 &&
          vs[s].priority < 7) {
        switch (vs[s].priority) {
          case 2:
            if (strcmp(vs[s].value, "sin") == 0)
              *res = sin(vs[s - 2].num + vs[s - 1].num);
            if (strcmp(vs[s].value, "cos") == 0)
              *res = cos(vs[s - 2].num + vs[s - 1].num);
            if (strcmp(vs[s].value, "asin") == 0)
              *res = asin(vs[s - 2].num + vs[s - 1].num);
            if (strcmp(vs[s].value, "acos") == 0)
              *res = acos(vs[s - 2].num + vs[s - 1].num);
            if (strcmp(vs[s].value, "tan") == 0)
              *res = tan(vs[s - 2].num + vs[s - 1].num);
            if (strcmp(vs[s].value, "atan") == 0)
              *res = atan(vs[s - 2].num + vs[s - 1].num);
            if (strcmp(vs[s].value, "ln") == 0)
              *res = log(vs[s - 2].num + vs[s - 1].num);
            if (strcmp(vs[s].value, "log") == 0)
              *res = log10(vs[s - 2].num + vs[s - 1].num);
            if (strcmp(vs[s].value, "sqrt") == 0)
              *res = sqrt(vs[s - 2].num + vs[s - 1].num);
            break;
          case 3:
            if (vs[s].value[0] == '^') *res = pow(vs[s - 2].num, vs[s - 1].num);
            break;
          case 6:
          case 5:
            if (vs[s].value[0] == '+') *res = vs[s - 2].num + vs[s - 1].num;
            if (vs[s].value[0] == '-') *res = vs[s - 2].num - vs[s - 1].num;
            break;
          case 4:
            if (vs[s].value[0] == '*') *res = vs[s - 2].num * vs[s - 1].num;
            if (vs[s].value[0] == '/') {
              if (vs[s - 1].num == 0 && vs[s - 1].value[0] != 'x')
                ret_flag = 3;
              else
                *res = vs[s - 2].num / vs[s - 1].num;
            }
            if (vs[s].value[0] == '%') {
              *res = fmod(vs[s - 2].num, vs[s - 1].num);
            }
            break;
        }
        sprintf(vs[s - 2].value, "%lf", *res);
        vs[s - 2].priority = 7;
        vs[s - 2].num = *res;
        for (int z = s + 1; z < cnt_vs; z++) {
          strcpy(vs[z - 2].value, vs[z].value);
          vs[z - 2].priority = vs[z].priority;
          vs[z - 2].num = vs[z].num;
        }
        vs[cnt_vs - 2].value[0] = '\0';
        vs[cnt_vs - 2].priority = 0;
        vs[cnt_vs - 2].num = 0;
        vs[cnt_vs - 1].value[0] = '\0';
        vs[cnt_vs - 1].priority = 0;
        vs[cnt_vs - 1].num = 0;
        cnt_vs -= 2;
        break;
      }
    }
  }
  return ret_flag;
}

void obnul(int *cnt_stek, Lexemes *stek) {
  for (int k = *cnt_stek; k >= 0; k--) {
    stek[k].value[0] = '\0';
    stek[k].priority = 0;
    stek[k].num = 0;
  }
  *cnt_stek = 0;
}

void add_to_stek_from_Lexeme(int k, Lexemes *Lexeme, int *cnt_stek,
                             Lexemes *stek) {
  strcpy(stek[*cnt_stek].value, Lexeme[k].value);
  stek[*cnt_stek].priority = Lexeme[k].priority;
  stek[*cnt_stek].num = Lexeme[k].num;
  *cnt_stek += 1;
}

void add_to_vs_from_Lexeme(int k, Lexemes *Lexeme, int *cnt_vs, Lexemes *vs) {
  strcpy(vs[*cnt_vs].value, Lexeme[k].value);
  vs[*cnt_vs].priority = Lexeme[k].priority;
  vs[*cnt_vs].num = Lexeme[k].num;
  *cnt_vs += 1;
}

void add_to_vs_from_stek(int cnt_stek, Lexemes *stek, int *cnt_vs,
                         Lexemes *vs) {
  for (int i = cnt_stek - 1; i >= 0; i--) {
    strcpy(vs[*cnt_vs].value, stek[i].value);
    vs[*cnt_vs].priority = stek[i].priority;
    vs[*cnt_vs].num = stek[i].num;
    *cnt_vs += 1;
  }
}

void add_to_vs_stek_zero(int *cnt_vs, Lexemes *vs) {
  vs[*cnt_vs].value[0] = '0';
  vs[*cnt_vs].priority = 7;
  vs[*cnt_vs].num = 0;
  *cnt_vs += 1;
}

void add_to_vs_from_stek_one(int *cnt_stek, Lexemes *stek, int *cnt_vs,
                             Lexemes *vs) {
  strcpy(vs[*cnt_vs].value, stek[*cnt_stek - 1].value);
  vs[*cnt_vs].priority = stek[*cnt_stek - 1].priority;
  vs[*cnt_vs].num = stek[*cnt_stek - 1].num;
  *cnt_vs += 1;
  stek[*cnt_stek - 1].value[0] = '\0';
  stek[*cnt_stek - 1].priority = 0;
  stek[*cnt_stek - 1].num = 0;
  *cnt_stek -= 1;
}

void free_stek_to_bracket(int *cnt_stek, Lexemes *stek, int *cnt_vs,
                          Lexemes *vs) {
  do {
    strcpy(vs[*cnt_vs].value, stek[*cnt_stek - 1].value);
    vs[*cnt_vs].priority = stek[*cnt_stek - 1].priority;
    vs[*cnt_vs].num = stek[*cnt_stek - 1].num;
    *cnt_vs += 1;
    stek[*cnt_stek - 1].value[0] = '\0';
    stek[*cnt_stek - 1].priority = 0;
    stek[*cnt_stek - 1].num = 0;
    *cnt_stek -= 1;
  } while (stek[*cnt_stek - 1].value[0] != '(');
  stek[*cnt_stek - 1].value[0] = '\0';
  stek[*cnt_stek - 1].priority = 0;
  stek[*cnt_stek - 1].num = 0;
  *cnt_stek -= 1;
}

void priority_OPN(int *k, Lexemes *Lexeme, int *cnt_vs, Lexemes *vs,
                  int *cnt_stek, Lexemes *stek, int openFlag) {
  if (*cnt_stek == 0) {
    add_to_stek_from_Lexeme(*k, Lexeme, &*cnt_stek, stek);
  } else

      if (stek[*cnt_stek - 1].value[0] == '(') {
    add_to_stek_from_Lexeme(*k, Lexeme, &*cnt_stek, stek);
  } else

      if (stek[*cnt_stek - 1].priority == Lexeme[*k].priority) {
    if (stek[*cnt_stek - 1].value[0] == '^' && Lexeme[*k].value[0] == '^') {
      add_to_stek_from_Lexeme(*k, Lexeme, &*cnt_stek, stek);
    } else {
      add_to_vs_from_stek_one(&*cnt_stek, stek, &*cnt_vs, vs);
      add_to_stek_from_Lexeme(*k, Lexeme, &*cnt_stek, stek);
    }
  } else

      if (stek[*cnt_stek - 1].priority < Lexeme[*k].priority) {
    if (openFlag > 0) {
      do {
        add_to_vs_from_stek_one(&*cnt_stek, stek, &*cnt_vs, vs);
      } while (stek[*cnt_stek - 1].priority <= Lexeme[*k].priority &&
               *cnt_stek != 0 && stek[*cnt_stek - 1].priority < 1);
    } else {
      do {
        add_to_vs_from_stek_one(&*cnt_stek, stek, &*cnt_vs, vs);
      } while (stek[*cnt_stek - 1].priority <= Lexeme[*k].priority &&
               *cnt_stek != 0);
    }
    add_to_stek_from_Lexeme(*k, Lexeme, &*cnt_stek, stek);
  } else

      if (stek[*cnt_stek - 1].priority > Lexeme[*k].priority) {
    add_to_stek_from_Lexeme(*k, Lexeme, &*cnt_stek, stek);
  }
}
