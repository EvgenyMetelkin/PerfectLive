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
    set0 << 37020 << 50828 << 54600;
    set1 << 35172 << 36804 << 60531;
    set2 << 18000 << 18000 << 18000;
    set3 << 80 << 137 << 254;
    set4 << 7000 << 0 << 0;
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
