#include "mainwindow.h"

#include <QByteArray>
#include <QDate>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>
#include <QTextEdit>
#include <ctime>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->tabWidget->setCurrentIndex(0);
  ui->tabWidget->setFixedSize(1250, 410);
  this->setFixedSize(1250, 410);

  // calculator

  ui->LineEdit_Xmax->setValidator(new QIntValidator(-1000000, 999999, this));
  ui->LineEdit_Xmin->setValidator(new QIntValidator(-1000000, 999999, this));
  ui->LineEdit_Ymin->setValidator(new QIntValidator(-1000000, 999999, this));
  ui->LineEdit_Ymax->setValidator(new QIntValidator(-1000000, 999999, this));

  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digitalNumbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digitalNumbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digitalNumbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digitalNumbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digitalNumbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digitalNumbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digitalNumbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digitalNumbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digitalNumbers()));
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digitalNumbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digitalNumbers()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_delim, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_XinY, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_openBracket, SIGNAL(clicked()), this,
          SLOT(operations()));
  connect(ui->pushButton_closeBracket, SIGNAL(clicked()), this,
          SLOT(operations()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(operations_fun()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(operations_fun()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(operations_fun()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(operations_fun()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(operations_fun()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(operations_fun()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(operations_fun()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(operations_fun()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(operations_fun()));
  connect(ui->lineEdit, SIGNAL(returnPressed()), this,
          SLOT(on_pushButton_result_clicked()));

  // credit

  ui->comboBox->addItem("Years", QVariant(1));
  ui->comboBox->addItem("Months", QVariant(1));
  ui->tableWidget->setRowCount(1);
  ui->tableWidget->setColumnCount(6);
  ui->tableWidget->setItem(0, 0, new QTableWidgetItem("№"));
  ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Month"));
  ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Payment amount"));
  ui->tableWidget->setItem(0, 3, new QTableWidgetItem("Principal payment"));
  ui->tableWidget->setItem(0, 4, new QTableWidgetItem("Interest payment"));
  ui->tableWidget->setItem(0, 5, new QTableWidgetItem("Remaining debt"));
  ui->tableWidget->setRowHeight(0, 50);
  ui->tableWidget->setColumnWidth(0, 45);
  ui->tableWidget->setColumnWidth(1, 118);
  ui->tableWidget->setColumnWidth(2, 117);
  ui->tableWidget->setColumnWidth(3, 117);
  ui->tableWidget->setColumnWidth(4, 117);
  ui->tableWidget->setColumnWidth(5, 117);
  ui->tableWidget->verticalHeader()->setVisible(false);
  ui->tableWidget->horizontalHeader()->setVisible(false);

  ui->lineEdit_countMon->setValidator(new QIntValidator(1, 60, this));
  ui->lineEdit_sum->setValidator(new QIntValidator(1000, 10000000, this));
  ui->lineEdit_perc->setValidator(new QIntValidator(1, 100, this));

  ui->tableWidget->setWordWrap(true);

  // deposit

  ui->tableWidget_dep->setRowCount(1);
  ui->tableWidget_dep->setColumnCount(5);
  ui->tableWidget_dep->setItem(0, 0, new QTableWidgetItem("№"));
  ui->tableWidget_dep->setItem(0, 1, new QTableWidgetItem("Month"));
  ui->tableWidget_dep->setItem(0, 2, new QTableWidgetItem("Percent"));
  ui->tableWidget_dep->setItem(0, 3,
                               new QTableWidgetItem("Deposit replenished"));
  ui->tableWidget_dep->setItem(0, 4, new QTableWidgetItem("Balance of depos"));
  ui->tableWidget_dep->item(0, 0)->setForeground(QBrush(QColor(255, 255, 255)));
  ui->tableWidget_dep->item(0, 1)->setForeground(QBrush(QColor(255, 255, 255)));
  ui->tableWidget_dep->item(0, 2)->setForeground(QBrush(QColor(255, 255, 255)));
  ui->tableWidget_dep->item(0, 3)->setForeground(QBrush(QColor(255, 255, 255)));
  ui->tableWidget_dep->item(0, 4)->setForeground(QBrush(QColor(255, 255, 255)));
  ui->tableWidget_dep->setRowHeight(0, 50);
  ui->tableWidget_dep->setColumnWidth(0, 45);
  ui->tableWidget_dep->setColumnWidth(1, 135);
  ui->tableWidget_dep->setColumnWidth(2, 117);
  ui->tableWidget_dep->setColumnWidth(3, 117);
  ui->tableWidget_dep->setColumnWidth(4, 117);
  ui->tableWidget_dep->setWordWrap(true);
  ui->tableWidget_dep->verticalHeader()->setVisible(false);
  ui->tableWidget_dep->horizontalHeader()->setVisible(false);
  ui->tableWidget_dep->alternatingRowColors();
  ui->tableWidget_tax->setColumnCount(2);
  ui->tableWidget_tax->setColumnWidth(0, 120);
  ui->tableWidget_tax->setColumnWidth(1, 120);
  ui->tableWidget_tax->setWordWrap(true);
  ui->tableWidget_tax->verticalHeader()->setVisible(false);
  ui->tableWidget_tax->horizontalHeader()->setVisible(false);

  ui->comboBox_count_dep->addItem("Days", QVariant(0));
  ui->comboBox_count_dep->addItem("Months", QVariant(1));
  ui->comboBox_count_dep->addItem("Years", QVariant(2));

  ui->comboBox_period_vklada->addItem("End of term", QVariant(0));
  ui->comboBox_period_vklada->addItem("Daily", QVariant(1));
  ui->comboBox_period_vklada->addItem("Weekly", QVariant(2));
  ui->comboBox_period_vklada->addItem("Monthly", QVariant(3));
  ui->comboBox_period_vklada->addItem("Quarterly", QVariant(4));
  ui->comboBox_period_vklada->addItem("Half-yearly", QVariant(5));
  ui->comboBox_period_vklada->addItem("Yerly", QVariant(6));

  ui->comboBox_period_in->addItem("Once", QVariant(0));
  ui->comboBox_period_in->addItem("Monthly", QVariant(1));
  ui->comboBox_period_in->addItem("Bimonthly", QVariant(2));
  ui->comboBox_period_in->addItem("Quarterly", QVariant(3));
  ui->comboBox_period_in->addItem("Half-yearly", QVariant(4));
  ui->comboBox_period_in->addItem("Yerly", QVariant(5));

  ui->comboBox_period_out->addItem("Once", QVariant(0));
  ui->comboBox_period_out->addItem("Monthly", QVariant(1));
  ui->comboBox_period_out->addItem("Bimonthly", QVariant(2));
  ui->comboBox_period_out->addItem("Quarterly", QVariant(3));
  ui->comboBox_period_out->addItem("Half-yearly", QVariant(4));
  ui->comboBox_period_out->addItem("Yerly", QVariant(5));

  ui->dateEdit_vklada->setDate(QDate::currentDate());
  ui->dateEdit_vklada->setMinimumDate(QDate::currentDate());

  ui->dateEdit_in->setDate(QDate::currentDate());
  ui->dateEdit_in->setMinimumDate(QDate::currentDate());

  ui->dateEdit_out->setDate(QDate::currentDate());
  ui->dateEdit_out->setMinimumDate(QDate::currentDate());

  ui->lineEdit_sum_dep->setValidator(new QIntValidator(100, 10000000, this));
  ui->lineEdit_sum_in->setValidator(new QIntValidator(100, 1000000, this));
  ui->lineEdit_sum_out->setValidator(new QIntValidator(100, 1000000, this));
  ui->lineEdit_countMon->setValidator(new QIntValidator(1, 60, this));
  ui->lineEdit_perc_dep->setValidator(new QIntValidator(1, 100, this));
}

MainWindow::~MainWindow() { delete ui; }

//
// calculator
//

void MainWindow::digitalNumbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_edit;

  new_edit = ui->lineEdit->text() + button->text();
  ui->lineEdit->setText(new_edit);
}

void MainWindow::on_pushButton_dot_clicked() {
  if (!(ui->lineEdit->text().contains('.')))
    ui->lineEdit->setText(ui->lineEdit->text() + ".");
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();
  QString new_edit;

  if (button->text() == "xʸ")
    new_edit = ui->lineEdit->text() + "^";
  else
    new_edit = ui->lineEdit->text() + button->text();
  ui->lineEdit->setText(new_edit);
}

void MainWindow::operations_fun() {
  QPushButton *button = (QPushButton *)sender();

  QString new_edit;

  if (button->text() == "√")
    new_edit = ui->lineEdit->text() + "sqrt(";
  else
    new_edit = ui->lineEdit->text() + button->text() + "(";
  ui->lineEdit->setText(new_edit);
}

void MainWindow::on_pushButton_result_clicked() {
  if (ui->lineEdit->text().contains('x') && ui->lineEdit_x->text() != "") {
    QByteArray ba = ui->lineEdit->text().toLocal8Bit();
    char *str = ba.data();
    char mistake[100];
    double result, x;
    x = ui->lineEdit_x->text().toDouble();
    int otvet = my_SmartCalc(str, x, &result, mistake);
    if (otvet == 1) {
      QString m = mistake;
      ui->resultLabel->setText(m);
    } else {
      ui->resultLabel->setText(QString::number(result));
    }
  }
  if (ui->lineEdit->text().contains('x') && ui->lineEdit_x->text() == "") {
    ui->resultLabel->setText("enter x or create graphic");
  }

  if (!(ui->lineEdit->text().contains('x'))) {
    QByteArray ba = ui->lineEdit->text().toLocal8Bit();
    char *str = ba.data();
    char mistake[100];
    double result;
    int otvet = my_SmartCalc(str, 0, &result, mistake);
    if (otvet == 1) {
      QString m = mistake;
      ui->resultLabel->setText(m);
    } else {
      ui->resultLabel->setText(QString::number(result));
    }
  }
}

void MainWindow::on_pushButton_AC_clicked() {
  ui->resultLabel->setText("");
  ui->lineEdit->setText("");
  ui->lineEdit_x->setText("");
}

void MainWindow::on_pushButton_C_clicked() {
  if (ui->lineEdit->text() != "") {
    QString edit = ui->lineEdit->text();
    edit.resize(edit.size() - 1);
    ui->lineEdit->setText(edit);
  } else {
    QString lable = ui->resultLabel->text();
    lable.resize(lable.size() - 1);
    ui->resultLabel->setText(lable);
  }
}

void MainWindow::on_pushButton_createGraphic_clicked() {
  QByteArray ba = ui->lineEdit->text().toLocal8Bit();
  char *str = ba.data();
  char mistake[100];
  double result;
  int otvet = my_SmartCalc(str, 0, &result, mistake);

  if (otvet == 1) {
    QString m = mistake;
    ui->resultLabel->setText(m);
  } else {
    ui->widget->clearGraphs();
    x.clear();
    y.clear();

    h = ui->LineEdit_step->text().toDouble();
    Xmin = ui->LineEdit_Xmin->text().toDouble();
    Xmax = ui->LineEdit_Xmax->text().toDouble();

    Ymin = ui->LineEdit_Ymin->text().toDouble();
    Ymax = ui->LineEdit_Ymax->text().toDouble();

    ui->widget->xAxis->setRange(Xmin, Xmax);
    ui->widget->yAxis->setRange(Ymin, Ymax);

    N = (Xmax - Xmin) / h + 2;
    X = Xmin;
    if (ui->Slowly->isChecked() == true) {
      timer = new QTimer(this);
      connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
      timer->start(5);
    } else {
      for (X = Xmin; X <= Xmax; X = X + h) {
        my_SmartCalc(str, X, &result, mistake);
        x.push_back(X);
        y.push_back(result);
      }
      ui->widget->addGraph();
      ui->widget->graph(0)->addData(x, y);
      ui->widget->replot();

      ui->widget->setInteraction(QCP::iRangeZoom, true);
      ui->widget->setInteraction(QCP::iRangeDrag, true);
    }
  }
}

void MainWindow::TimerSlot() {
  QByteArray ba = ui->lineEdit->text().toLocal8Bit();
  char *str = ba.data();
  char mistake[100];
  double result;
  int otvet;
  if (time_graphic <= 5 * N) {
    if (X <= Xmax) {
      otvet = my_SmartCalc(str, X, &result, mistake);
      if (otvet == 1) {
        QString m = mistake;
        ui->resultLabel->setText(m);
      } else {
        x.push_back(X);
        y.push_back(result);
        X += h;
      }
    }
    time_graphic += 5;
  } else {
    time_graphic = 0;
    timer->stop();
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();

  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
}

//
// credit
//

void MainWindow::on_pushButton_creditCalc_clicked() {
  int count_mon;

  if (ui->comboBox->currentText() == "Years")
    count_mon = 12 * ui->lineEdit_countMon->text().toInt();
  if (ui->comboBox->currentText() == "Months")
    count_mon = ui->lineEdit_countMon->text().toInt();

  creditStruct credits[count_mon];

  double sum = ui->lineEdit_sum->text().toInt();
  int perc = ui->lineEdit_perc->text().toInt();
  double sum_perc = 0;
  double sum_sumPerc = 0;

  ui->tableWidget->setRowCount(count_mon + 1);

  int variant = 0;
  if (ui->radioButton_1->isChecked()) variant = 1;
  if (ui->radioButton_2->isChecked()) variant = 2;

  credit(sum, count_mon, perc, credits, variant, &sum_perc, &sum_sumPerc);
  for (int i = 1; i <= count_mon; i++) {
    ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
    ui->tableWidget->setItem(
        i, 1,
        new QTableWidgetItem(QString::fromLocal8Bit(credits[i - 1].mon) + " " +
                             QString::number(credits[i - 1].year)));
    ui->tableWidget->setItem(
        i, 2,
        new QTableWidgetItem(QString::number(credits[i - 1].sum_pay, 'g', 10)));
    ui->tableWidget->setItem(i, 3,
                             new QTableWidgetItem(QString::number(
                                 credits[i - 1].pay_of_main_credit, 'g', 10)));
    ui->tableWidget->setItem(i, 4,
                             new QTableWidgetItem(QString::number(
                                 credits[i - 1].pay_of_precent, 'g', 10)));
    ui->tableWidget->setItem(i, 5,
                             new QTableWidgetItem(QString::number(
                                 credits[i - 1].balance_of_debt, 'g', 10)));
  }
  if (variant == 1)
    ui->label_mon_pay->setText(QString::number(credits[0].sum_pay, 'g', 10));
  if (variant == 2)
    ui->label_mon_pay->setText(
        "max pay\n" + QString::number(credits[0].sum_pay, 'g', 10) +
        "\n\nmin pay \n" +
        QString::number(credits[count_mon - 1].sum_pay, 'g', 10));
  ui->label_perc->setText(QString::number(sum_perc, 'g', 10));
  ui->label_sum_perc->setText(QString::number(sum + sum_perc, 'g', 10));
}

void MainWindow::on_horSlider_count_valueChanged(int value) {
  int val = ui->horSlider_count->value();
  ui->lineEdit_countMon->setText(QString::number(val));
}

void MainWindow::on_lineEdit_countMon_textChanged(const QString &arg1) {
  ui->horSlider_count->setValue(ui->lineEdit_countMon->text().toInt());
}

void MainWindow::on_horSlider_sum_valueChanged(int value) {
  int val = ui->horSlider_sum->value();
  ui->lineEdit_sum->setText(QString::number(val));
}

void MainWindow::on_lineEdit_sum_textChanged(const QString &arg1) {
  ui->horSlider_sum->setValue(ui->lineEdit_sum->text().toInt());
}

void MainWindow::on_horSlider_perc_valueChanged(int value) {
  int val = ui->horSlider_perc->value();
  ui->lineEdit_perc->setText(QString::number(val));
}

void MainWindow::on_lineEdit_perc_textChanged(const QString &arg1) {
  ui->horSlider_perc->setValue(ui->lineEdit_perc->text().toInt());
}

//
// depos
//

void MainWindow::on_horSlider_count_dep_valueChanged(int value) {
  int val = ui->horSlider_count_dep->value();
  ui->lineEdit_countMon_dep->setText(QString::number(val));
}

void MainWindow::on_lineEdit_countMon_dep_textChanged(const QString &arg1) {
  ui->horSlider_count_dep->setValue(ui->lineEdit_countMon_dep->text().toInt());
}

void MainWindow::on_horSlider_sum_dep_valueChanged(int value) {
  int val = ui->horSlider_sum_dep->value();
  ui->lineEdit_sum_dep->setText(QString::number(val));
}

void MainWindow::on_lineEdit_sum_dep_textChanged(const QString &arg1) {
  ui->horSlider_sum_dep->setValue(ui->lineEdit_sum_dep->text().toInt());
}

void MainWindow::on_horSlider_perc_dep_valueChanged(int value) {
  int val = ui->horSlider_perc_dep->value();
  ui->lineEdit_perc_dep->setText(QString::number(val));
}

void MainWindow::on_lineEdit_perc_dep_textChanged(const QString &arg1) {
  ui->horSlider_perc_dep->setValue(ui->lineEdit_perc_dep->text().toInt());
}

void MainWindow::on_horSlider_sum_in_valueChanged(int value) {
  int val = ui->horSlider_sum_in->value();
  ui->lineEdit_sum_in->setText(QString::number(val));
}

void MainWindow::on_lineEdit_sum_in_textChanged(const QString &arg1) {
  ui->horSlider_sum_in->setValue(ui->lineEdit_sum_in->text().toInt());
}

void MainWindow::on_horSlider_sum_out_valueChanged(int value) {
  int val = ui->horSlider_sum_out->value();
  ui->lineEdit_sum_out->setText(QString::number(val));
}

void MainWindow::on_lineEdit_sum_out_textChanged(const QString &arg1) {
  ui->horSlider_sum_out->setValue(ui->lineEdit_sum_out->text().toInt());
}

void MainWindow::on_pushButton_depCalc_clicked() {
  if (ui->lineEdit_countMon_dep->text().toInt() <= 0)
    ui->lineEdit_countMon_dep->setText("1");
  if (ui->lineEdit_sum_dep->text().toDouble() <= 0)
    ui->lineEdit_sum_dep->setText("1000");
  if (ui->lineEdit_perc_dep->text().toDouble() <= 0)
    ui->lineEdit_perc_dep->setText("1");
  double sum_vklada = ui->lineEdit_sum_dep->text().toDouble();
  int period_vklada = ui->comboBox_period_vklada->currentIndex();
  int count_v = ui->lineEdit_countMon_dep->text().toInt();
  double perc_vklada = ui->lineEdit_perc_dep->text().toDouble();
  int start_d = ui->dateEdit_vklada->date().day();
  int start_m = ui->dateEdit_vklada->date().month();
  int start_y = ui->dateEdit_vklada->date().year();
  int flag_count_vklada = ui->comboBox_count_dep->currentIndex();

  int flag_in = 0;
  if (ui->checkBox_dep_in->isChecked() == true) flag_in = 1;
  double sum_in = ui->lineEdit_sum_in->text().toDouble();
  int period_in = ui->comboBox_period_in->currentIndex();
  int in_day = ui->dateEdit_in->date().day();
  int in_mon = ui->dateEdit_in->date().month();
  int in_year = ui->dateEdit_in->date().year();

  int flag_out = 0;
  if (ui->checkBox_dep_out->isChecked() == true) flag_out = 1;
  double sum_out = ui->lineEdit_sum_out->text().toDouble();
  int period_out = ui->comboBox_period_out->currentIndex();
  int out_day = ui->dateEdit_out->date().day();
  int out_mon = ui->dateEdit_out->date().month();
  int out_year = ui->dateEdit_out->date().year();

  double sum_tax = 0;
  double sum_perc = 0;
  double sum_balance_of_depos = 0;

  int capital = 0;
  if (ui->checkBox_capitalization->isChecked() == true) capital = 1;
  const double key_rate = 7.5;
  int count_debits = 0;

  int count_vklada =
      countDays(count_v, start_d, start_m - 1, start_y, flag_count_vklada);

  debitStruct debits[count_vklada + 123];

  deposit(sum_vklada, period_vklada, count_vklada, perc_vklada, start_d,
          start_m - 1, start_y - 1900, flag_in, sum_in, period_in, in_day,
          in_mon - 1, in_year - 1900, flag_out, sum_out, period_out, out_day,
          out_mon - 1, out_year - 1900, capital, debits, &count_debits,
          &sum_perc, &sum_balance_of_depos);

  ui->tableWidget_dep->setRowCount(count_debits + 1);

  for (int i = 1; i <= count_debits; i++) {
    ui->tableWidget_dep->setItem(i, 0,
                                 new QTableWidgetItem(QString::number(i)));
    ui->tableWidget_dep->setItem(
        i, 1,
        new QTableWidgetItem(QString::number(debits[i - 1].day) + " " +
                             QString::fromLocal8Bit(debits[i - 1].mon) + " " +
                             QString::number(debits[i - 1].year)));
    ui->tableWidget_dep->setItem(
        i, 2,
        new QTableWidgetItem(QString::number(debits[i - 1].percent, 'g', 10)));
    ui->tableWidget_dep->setItem(
        i, 3,
        new QTableWidgetItem(
            QString::number(debits[i - 1].deposit_replenished, 'g', 10)));
    if (debits[i - 1].deposit_replenished < 0) {
      ui->tableWidget_dep->item(i, 3)->setForeground(QBrush(QColor(Qt::red)));
    } else if (debits[i - 1].deposit_replenished > 0) {
      ui->tableWidget_dep->item(i, 3)->setForeground(QBrush(QColor(Qt::green)));
    } else {
      ui->tableWidget_dep->item(i, 3)->setForeground(
          QBrush(QColor(255, 255, 255)));
    }
    ui->tableWidget_dep->setItem(i, 4,
                                 new QTableWidgetItem(QString::number(
                                     debits[i - 1].balance_of_depos, 'g', 10)));

    ui->tableWidget_dep->item(i, 0)->setForeground(
        QBrush(QColor(255, 255, 255)));
    ui->tableWidget_dep->item(i, 1)->setForeground(
        QBrush(QColor(255, 255, 255)));
    ui->tableWidget_dep->item(i, 2)->setForeground(
        QBrush(QColor(255, 255, 255)));
    ui->tableWidget_dep->item(i, 4)->setForeground(
        QBrush(QColor(255, 255, 255)));
  }

  stractTax tax[debits[count_debits - 1].year - 2022];
  int count_tax = 0;

  tax_rent(debits, count_debits, key_rate, tax, &count_tax);

  ui->tableWidget_tax->setRowCount(count_tax);
  for (int i = 0; i < count_tax; i++) {
    ui->tableWidget_tax->setItem(
        i, 0,
        new QTableWidgetItem("tax for " + QString::number(tax[i].year) +
                             " year"));
    ui->tableWidget_tax->setItem(
        i, 1, new QTableWidgetItem(QString::number(tax[i].tax_year, 'g', 10)));
    sum_tax = sum_tax + tax[i].tax_year;
  }

  ui->label_sum_tax->setText(QString::number(sum_tax, 'g', 10));
  ui->label_sum_perc_dep->setText(QString::number(sum_perc, 'g', 10));
  ui->label_sum_perc_minus_tax->setText(
      QString::number(sum_perc - sum_tax, 'g', 10));
  ui->label_sum_balance_of_depos->setText(
      QString::number(sum_balance_of_depos, 'g', 10));
}

void MainWindow::on_tabWidget_currentChanged(int index) {
  if (ui->tabWidget->currentIndex() == 0) {
    this->setWindowTitle("Calculator");
    this->setFixedSize(1250, 410);
    ui->tabWidget->setFixedSize(1250, 410);
  }

  if (ui->tabWidget->currentIndex() == 1) {
    this->setWindowTitle("Credit calc");
    this->setFixedSize(1210, 410);
    ui->tabWidget->setFixedSize(1210, 410);
  }

  if (ui->tabWidget->currentIndex() == 2) {
    this->setWindowTitle("Deposit calc");
    this->setFixedSize(1093, 770);
    ui->tabWidget->setFixedSize(1093, 770);
  }
}

void MainWindow::on_checkBox_dep_in_clicked() {
  if (ui->checkBox_dep_in->isChecked() == true) {
    ui->label_in->setEnabled(true);
    ui->label_date_in->setEnabled(true);
    ui->label_period_in->setEnabled(true);
    ui->horSlider_sum_in->setEnabled(true);
    ui->lineEdit_sum_in->setEnabled(true);
    ui->dateEdit_in->setEnabled(true);
    ui->comboBox_period_in->setEnabled(true);
  } else {
    ui->label_in->setEnabled(false);
    ui->label_date_in->setEnabled(false);
    ui->label_period_in->setEnabled(false);
    ui->lineEdit_sum_in->setEnabled(false);
    ui->horSlider_sum_in->setEnabled(false);
    ui->dateEdit_in->setEnabled(false);
    ui->comboBox_period_in->setEnabled(false);
  }
}

void MainWindow::on_checkBox_dep_out_clicked() {
  if (ui->checkBox_dep_out->isChecked() == true) {
    ui->label_out->setEnabled(true);
    ui->label_date_out->setEnabled(true);
    ui->label_period_out->setEnabled(true);
    ui->horSlider_sum_out->setEnabled(true);
    ui->lineEdit_sum_out->setEnabled(true);
    ui->dateEdit_out->setEnabled(true);
    ui->comboBox_period_out->setEnabled(true);
  } else {
    ui->label_out->setEnabled(false);
    ui->label_date_out->setEnabled(false);
    ui->label_period_out->setEnabled(false);
    ui->lineEdit_sum_out->setEnabled(false);
    ui->horSlider_sum_out->setEnabled(false);
    ui->dateEdit_out->setEnabled(false);
    ui->comboBox_period_out->setEnabled(false);
  }
}

void MainWindow::on_comboBox_count_dep_currentIndexChanged(int index) {
  if (ui->comboBox_count_dep->currentIndex() == 0) {
    ui->lineEdit_countMon_dep->setValidator(new QIntValidator(1, 100, this));
    ui->horSlider_count_dep->setMinimum(1);
    ui->horSlider_count_dep->setMaximum(100);
  }
  if (ui->comboBox_count_dep->currentIndex() == 1) {
    ui->lineEdit_countMon_dep->setValidator(new QIntValidator(1, 36, this));
    ui->horSlider_count_dep->setMinimum(1);
    ui->horSlider_count_dep->setMaximum(36);
  }
  if (ui->comboBox_count_dep->currentIndex() == 2) {
    ui->lineEdit_countMon_dep->setValidator(new QIntValidator(1, 5, this));
    ui->horSlider_count_dep->setMinimum(1);
    ui->horSlider_count_dep->setMaximum(5);
  }
}
