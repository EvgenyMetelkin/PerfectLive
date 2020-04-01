#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "WiseLine/wiselineparser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_incomeView(new IncomeView(this))
{
    ui->setupUi(this);

    m_passwordWidget.show();

    connect(&m_passwordWidget, &PasswordWidget::ConfirmedPassword, this, &MainWindow::ConfirmedPassword);

    ui->lWiseLine->setText(WiseLineParser::GetWiseLine());
    connect(&m_timerWiseLine, &QTimer::timeout, this, &MainWindow::NextWiseLine);
    m_timerWiseLine.start(100000);

    ViewIncome();
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

void MainWindow::ViewIncome()
{
    ui->gridLayout->addWidget(m_incomeView->GetIncomeView());
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

void MainWindow::on_bChangeWiseLine_clicked()
{
    ui->lWiseLine->setText(WiseLineParser::GetWiseLine());
}

void MainWindow::NextWiseLine()
{
    ui->lWiseLine->setText(WiseLineParser::GetWiseLine());
}
