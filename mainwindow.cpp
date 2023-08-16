#include "mainwindow.h"
#include "calculate.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  calculate = new Calculate();
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
  delete calculate;
}

void MainWindow::on_calculate_clicked() {
  QString expression = ui->textEdit->toPlainText();
  ui->calculated->setText(calculate->calculate(expression.replace(" ", "")));
}

void MainWindow::on_currencyCheck_clicked() {
  ui->calculated->setText(calculate->getExchangeRates());
}

void MainWindow::on_pushButton_clicked() { this->calculate->update(); }

void MainWindow::on_pushButton_2_clicked() {
  ui->calculated->setText(calculate->help());
}
