#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "WiseLine/wiselineparser.h"
#include "Style/mainstyle.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_incomeView(new IncomeView(this)),
    m_historyDiary(new HistoryCreationDiary(this))
{
    ui->setupUi(this);

    m_passwordWidget.show();

    connect(&m_diaryWidget, &DiaryWidget::HideDiary, this, &MainWindow::show);

    connect(&m_passwordWidget, &PasswordWidget::confirmedPassword, this, &MainWindow::confirmedPassword);

    ui->lWiseLine->setText(WiseLineParser::GetWiseLine());
    connect(&m_timerWiseLine, &QTimer::timeout, this, &MainWindow::nextWiseLine);
    m_timerWiseLine.start(100000);

    showIncome();

    // Устанавливаем данную палитру
    MainStyle mainStyle;
    qApp->setPalette(mainStyle);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_incomeView;
}

void MainWindow::showMainWindow()
{
    m_passwordWidget.hide();
    this->show();
}

void MainWindow::showIncome()
{
    ui->chartLayout->addWidget(m_incomeView);

    ui->lEarnByHour->setText(m_incomeView->getEarnByHour());
    ui->lTotalIncome->setText(m_incomeView->getTotalIncome());
}

void MainWindow::showHistoryDiary()
{
    ui->layoutHistoryDiary->addWidget(m_historyDiary);
}

void MainWindow::confirmedPassword()
{
    showMainWindow();
}

void MainWindow::on_bDiary_clicked()
{
    this->hide();
    m_diaryWidget.show(); // ! нет кнопки выхода
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

void MainWindow::nextWiseLine()
{
    ui->lWiseLine->setText(WiseLineParser::GetWiseLine());
}

void MainWindow::on_bCensus_clicked()
{
    this->hide();
    m_censusWidget.show(); // ! нет кнопки выхода
}
