#include "incomeview.h"

#include <QDebug>

IncomeView::IncomeView(QWidget *parent) :
    QChartView(new QChart(), parent),
    m_incomeView(new QChartView),
    m_setSalary("Зарплата"),
    m_setFA("ФА"),
    m_setAlimony("Алименты"),
    m_setPassiveIncome("Пасивный доход"),
    m_setOther("Другое"),
    m_countMount(0)
{
    createChart();
    createEarnByHour();
}

IncomeView::~IncomeView()
{
    if(m_incomeView)
        delete m_incomeView;
}

QString IncomeView::getTotalIncome()
{
    return m_earnByHour.getTotalIncome();
}

QString IncomeView::getEarnByHour()
{
    return m_earnByHour.getEarnByHour();
}

void IncomeView::initialize()
{
    openEarnFile();

    QTextStream in(&m_earnFile);
    while (!in.atEnd()) {
        in.readLine();
        int mount, salary, fa, alimony, passiveIncome, other;
        in >> mount >> salary >> fa >> alimony >> passiveIncome >> other;
        if((salary + fa + alimony + passiveIncome + other) != 0) {
            m_setSalary << salary;
            m_setFA << fa;
            m_setAlimony << alimony;
            m_setPassiveIncome << passiveIncome;
            m_setOther << other;
            m_sumIncome.append(QString::number(salary + fa + alimony + passiveIncome + other));
        } else {
            break;
        }
        m_countMount = mount;
    }
    m_earnFile.close();
}

void IncomeView::openEarnFile()
{
    // Сук, только сейчас понял что хотел это все сделать через бд...
    m_earnFile.setFileName("earn.txt"); // !! создать под это папку
    if (!m_earnFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        createEarnFile();

        if (!m_earnFile.open(QIODevice::ReadOnly | QIODevice::Text))
            exit(EXIT_FAILURE);
    }
}

void IncomeView::createEarnFile()
{
    qDebug() << Q_FUNC_INFO;
    m_earnFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&m_earnFile);
    out << QObject::tr("Месяц\t\tЗарплата\tФА\t\tАлименты\tВклады\t\tДругое");
    for(int mount = 1; mount <= 12; mount++) {
        out << endl << mount << "\t\t0\t\t0\t\t0\t\t0\t\t0";
    }
    m_earnFile.close();
}

void IncomeView::createChart()
{
    initialize();

    m_series.append(&m_setSalary);
    m_series.append(&m_setFA);
    m_series.append(&m_setAlimony);
    m_series.append(&m_setPassiveIncome);
    m_series.append(&m_setOther);

    chart()->addSeries(&m_series);
    chart()->setTitle("Income 2020");
    chart()->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;

    //[[clang::fallthrough]]; жуткая вещь, нужна чтобы компилятор не ругался на отсутствие break
    switch(m_countMount) {
    case 12:
        categories.push_front("Dec +" + m_sumIncome.at(11));
    [[clang::fallthrough]]; case 11:
        categories.push_front("Nov +" + m_sumIncome.at(10));
    [[clang::fallthrough]]; case 10:
        categories.push_front("Oct +" + m_sumIncome.at(9));
    [[clang::fallthrough]]; case 9:
        categories.push_front("Sept +" + m_sumIncome.at(8));
    [[clang::fallthrough]]; case 8:
        categories.push_front("Aug +" + m_sumIncome.at(7));
    [[clang::fallthrough]]; case 7:
        categories.push_front("Jul +" + m_sumIncome.at(6));
    [[clang::fallthrough]]; case 6:
        categories.push_front("Jun +" + m_sumIncome.at(5));
    [[clang::fallthrough]]; case 5:
        categories.push_front("May +" + m_sumIncome.at(4));
    [[clang::fallthrough]]; case 4:
        categories.push_front("Apr +" + m_sumIncome.at(3));
    [[clang::fallthrough]]; case 3:
        categories.push_front("Mar +" + m_sumIncome.at(2));
    [[clang::fallthrough]]; case 2:
        categories.push_front("Feb +" + m_sumIncome.at(1));
    [[clang::fallthrough]]; case 1:
        categories.push_front("Jan +" + m_sumIncome.at(0));
    }

    m_axisX.append(categories);
    chart()->addAxis(&m_axisX, Qt::AlignBottom);
    m_series.attachAxis(&m_axisX);

    chart()->addAxis(&m_axisY, Qt::AlignLeft);
    m_series.attachAxis(&m_axisY);

    chart()->legend()->setVisible(true);
    chart()->legend()->setAlignment(Qt::AlignBottom);

    m_incomeView->setRenderHint(QPainter::Antialiasing);
}

void IncomeView::createEarnByHour()
{
    m_earnByHour.create(m_sumIncome);
}
