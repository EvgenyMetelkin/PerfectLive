#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "WiseLine/wiselineparser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_passwordWidget.show();

    connect(&m_passwordWidget, &PasswordWidget::ConfirmedPassword, this, &MainWindow::ConfirmedPassword);

    ui->lWiseLine->setText(WiseLineParser::GetWiseLine());
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

void MainWindow::ConfirmedPassword()
{
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
