#include "incomeview.h"


#define COUNT_MOUNT 12

IncomeView::IncomeView(QWidget *parent) :
    QObject(parent),
    m_incomeView(new QChartView),
    set0("Зарплата"),
    set1("ФА"),
    set2("Алименты"),
    set3("Вклады"),
    set4("Другое")
{
    CreateChart();
}

IncomeView::~IncomeView()
{
    if(m_incomeView)
        delete m_incomeView; 
}

QChartView *IncomeView::GetIncomeView()
{
    return m_incomeView;
}

void IncomeView::Initialize()
{
    set0 << 10000 << 20000 << 30000 << 40000 << 50000 << 60000;
    set1 << 50000 << 00000 << 00000 << 40000 << 00000 << 70000;
    set2 << 30000 << 50000 << 80000 << 130000 << 80000 << 50000;
    set3 << 50000 << 60000 << 70000 << 30000 << 40000 << 50000;
    set4 << 90000 << 70000 << 50000 << 30000 << 10000 << 20000;
}

void IncomeView::CreateChart()
{
    Initialize();

    series.append(&set0);
    series.append(&set1);
    series.append(&set2);
    series.append(&set3);
    series.append(&set4);

    chart.addSeries(&series);
    chart.setTitle("Income 2020");
    chart.setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Aug" << "Sept" << "Oct" << "Nov" << "Dec";

    axisX.append(categories);
    chart.addAxis(&axisX, Qt::AlignBottom);
    series.attachAxis(&axisX);

    chart.addAxis(&axisY, Qt::AlignLeft);
    series.attachAxis(&axisY);

    chart.legend()->setVisible(true);
    chart.legend()->setAlignment(Qt::AlignBottom);

    m_incomeView->setChart(&chart);
    m_incomeView->setRenderHint(QPainter::Antialiasing);
}
