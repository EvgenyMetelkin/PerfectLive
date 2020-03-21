#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_mainMod(false)
{
    ui->setupUi(this);

    m_passwordWidget.show();

    connect(&m_passwordWidget, &PasswordWidget::confirmedBasePassword, this, &MainWindow::ConfirmedBasePassword);
    connect(&m_passwordWidget, &PasswordWidget::confirmedMainPassword, this, &MainWindow::ConfirmedMainPassword);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowMainWindow()
{
    m_passwordWidget.hide();
    this->show();
}

void MainWindow::ConfirmedBasePassword()
{
    m_mainMod = false;
    ShowMainWindow();
}

void MainWindow::ConfirmedMainPassword()
{
    m_mainMod = true;
    ShowMainWindow();
}

void MainWindow::on_bDiary_clicked()
{
    this->hide();
    m_diaryWidget.show(); // ! не скрываю окно и нет кнопки выхода
}

void MainWindow::on_bGoals_clicked()
{
    this->hide();
    m_goalsWidget.show();
}
