#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainMod(false)
{
    ui->setupUi(this);

    passwordWidget.show();

    connect(&passwordWidget, &PasswordWidget::confirmedBasePassword, this, &MainWindow::confirmedBasePassword);
    connect(&passwordWidget, &PasswordWidget::confirmedMainPassword, this, &MainWindow::confirmedMainPassword);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMainWindow()
{
    passwordWidget.hide();
    this->show();
}

void MainWindow::confirmedBasePassword()
{
    mainMod = false;
    showMainWindow();
}

void MainWindow::confirmedMainPassword()
{
    mainMod = true;
    showMainWindow();
}

void MainWindow::on_bDiary_clicked()
{
    this->hide();
    diaryWidget.show(); // !? не скрываю окно и нет кнопки выхода
}
