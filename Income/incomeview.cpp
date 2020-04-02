#include "incomeview.h"

#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

#define COUNT_MOUNT 12

IncomeView::IncomeView(QWidget *parent) :
    QObject(parent),
    m_incomeView(new QChartView),
    set0("Jane")
{
    CreateChart();
}

IncomeView::~IncomeView()
{
    if(m_incomeView)
        delete m_incomeView;

    for(auto barSet : m_listBarSet) {
        delete barSet;
    }
}

QChartView *IncomeView::GetIncomeView()
{
    return m_incomeView;
}

void IncomeView::Initialize()
{
    m_listBarSet[0] = new QBarSet("Jan");
    m_listBarSet[1] = new QBarSet("Feb");
    m_listBarSet[2] = new QBarSet("Mar");
    m_listBarSet[3] = new QBarSet("Apr");
    m_listBarSet[4] = new QBarSet("May");
    m_listBarSet[5] = new QBarSet("Jun");
    m_listBarSet[6] = new QBarSet("Jul");
    m_listBarSet[7] = new QBarSet("Aug");
    m_listBarSet[8] = new QBarSet("Sept");
    m_listBarSet[9] = new QBarSet("Oct");
    m_listBarSet[10] = new QBarSet("Nov");
    m_listBarSet[11] = new QBarSet("Dec");
}

void IncomeView::CreateChart()
{
    //Initialize();

//    m_listBarSet[0] << 1 << 2 << 3 << 4 << 5 << 6;
//    m_listBarSet[1] << 5 << 0 << 0 << 4 << 0 << 7;
//    m_listBarSet[2] << 3 << 5 << 8 << 13 << 8 << 5;
//    m_listBarSet[3] << 5 << 6 << 7 << 3 << 4 << 5;
//    m_listBarSet[4] << 9 << 7 << 5 << 3 << 1 << 2;

    QBarSet *set1 = new QBarSet("John");
    QBarSet *set2 = new QBarSet("Axel");
    QBarSet *set3 = new QBarSet("Mary");
    QBarSet *set4 = new QBarSet("Samantha");

    set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;


    QStackedBarSeries *series = new QStackedBarSeries();
    series->append(&set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    //![2]

    //![3]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple stackedbarchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //![3]

    //![4]
    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //![4]

    //![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //![5]

    //![6]
    m_incomeView->setChart(chart);
    m_incomeView->setRenderHint(QPainter::Antialiasing);
    //![6]
}
