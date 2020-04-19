#include "incomeview.h"

#include <QTextStream>
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
    CreateChart();
}

IncomeView::~IncomeView()
{
    if(m_incomeView)
        delete m_incomeView;
}

void IncomeView::Initialize()
{
    QFile file(":/personalInformation/earn.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
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
        } else {
            break;
        }
        m_countMount = mount;
    }
    file.close();
}

void IncomeView::CreateChart()
{
    Initialize();

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
        categories.push_front("Dec");
    [[clang::fallthrough]]; case 11:
        categories.push_front("Nov");
    [[clang::fallthrough]]; case 10:
        categories.push_front("Oct");
    [[clang::fallthrough]]; case 9:
        categories.push_front("Sept");
    [[clang::fallthrough]]; case 8:
        categories.push_front("Aug");
    [[clang::fallthrough]]; case 7:
        categories.push_front("Jul");
    [[clang::fallthrough]]; case 6:
        categories.push_front("Jun");
    [[clang::fallthrough]]; case 5:
        categories.push_front("May");
    [[clang::fallthrough]]; case 4:
        categories.push_front("Apr");
    [[clang::fallthrough]]; case 3:
        categories.push_front("Mar");
    [[clang::fallthrough]]; case 2:
        categories.push_front("Feb");
    [[clang::fallthrough]]; case 1:
        categories.push_front("Jan");
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
