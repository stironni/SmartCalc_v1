#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>

#include "qcustomplot.h"

extern "C" {
#include "s21_SmartCalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void digitalNumbers();
  void on_pushButton_dot_clicked();
  void operations();
  void operations_fun();

  void on_pushButton_result_clicked();

  void on_pushButton_AC_clicked();

  void on_pushButton_C_clicked();

  void on_pushButton_createGraphic_clicked();

  void TimerSlot();

  // credit calc

  void on_horSlider_count_valueChanged(int value);

  void on_horSlider_sum_valueChanged(int value);

  void on_horSlider_perc_valueChanged(int value);

  void on_lineEdit_sum_textChanged(const QString &arg1);

  void on_lineEdit_countMon_textChanged(const QString &arg1);

  void on_lineEdit_perc_textChanged(const QString &arg1);

  void on_pushButton_creditCalc_clicked();

  // deposit calc

  void on_horSlider_count_dep_valueChanged(int value);
  void on_lineEdit_countMon_dep_textChanged(const QString &arg1);

  void on_horSlider_sum_dep_valueChanged(int value);
  void on_lineEdit_sum_dep_textChanged(const QString &arg1);

  void on_horSlider_perc_dep_valueChanged(int value);
  void on_lineEdit_perc_dep_textChanged(const QString &arg1);

  void on_horSlider_sum_in_valueChanged(int value);
  void on_lineEdit_sum_in_textChanged(const QString &arg1);

  void on_horSlider_sum_out_valueChanged(int value);
  void on_lineEdit_sum_out_textChanged(const QString &arg1);

  void on_tabWidget_currentChanged(int index);

  void on_pushButton_depCalc_clicked();

  void on_checkBox_dep_in_clicked();
  void on_checkBox_dep_out_clicked();

  void on_comboBox_count_dep_currentIndexChanged(int index);

 private:
  Ui::MainWindow *ui;

  double Xmin, Xmax, Ymin, Ymax, h, X, Y;
  int N;
  QVector<double> x, y;
  QTimer *timer;
  int time_graphic;
};

class LineEdit : public QLineEdit {
 public:
  using QLineEdit::QLineEdit;

 protected:
  void mousePressEvent(QMouseEvent *event) {
    QLineEdit::mousePressEvent(event);
    setCursorPosition(0);
  }
};

#endif  // MAINWINDOW_H
