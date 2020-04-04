#include "incomeview.h"


#define COUNT_MOUNT 12

IncomeView::IncomeView(QWidget *parent) :
    QObject(parent),
    m_incomeView(new QChartView),
    m_set0("Зарплата"),
    m_set1("ФА"),
    m_set2("Алименты"),
    m_set3("Вклады"),
    m_set4("Другое")
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
    m_set0 << 37020 << 50828 << 54600;
    m_set1 << 35172 << 36804 << 60531;
    m_set2 << 18000 << 18000 << 18000;
    m_set3 << 80 << 137 << 254;
    m_set4 << 7000 << 0 << 0;
}

void IncomeView::CreateChart()
{
    Initialize();

    m_series.append(&m_set0);
    m_series.append(&m_set1);
    m_series.append(&m_set2);
    m_series.append(&m_set3);
    m_series.append(&m_set4);

    m_chart.addSeries(&m_series);
    m_chart.setTitle("Income 2020");
    m_chart.setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Aug" << "Sept" << "Oct" << "Nov" << "Dec";

    m_axisX.append(categories);
    m_chart.addAxis(&m_axisX, Qt::AlignBottom);
    m_series.attachAxis(&m_axisX);

    m_chart.addAxis(&m_axisY, Qt::AlignLeft);
    m_series.attachAxis(&m_axisY);

    m_chart.legend()->setVisible(true);
    m_chart.legend()->setAlignment(Qt::AlignBottom);

    m_incomeView->setChart(&m_chart);
    m_incomeView->setRenderHint(QPainter::Antialiasing);
}
