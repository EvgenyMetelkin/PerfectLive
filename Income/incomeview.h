#ifndef INCOMEVIEW_H
#define INCOMEVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

class IncomeView : public QObject
{
public:
    explicit IncomeView(QWidget *parent = nullptr);
    ~IncomeView();

    QChartView* GetIncomeView();

private:
    void Initialize();
    void CreateChart();

private:
    QChartView *m_incomeView;
    QBarSet m_set0;
    QBarSet m_set1;
    QBarSet m_set2;
    QBarSet m_set3;
    QBarSet m_set4;
    QStackedBarSeries m_series;
    QChart m_chart;
    QBarCategoryAxis m_axisX;
    QValueAxis m_axisY;
};

#endif // INCOMEVIEW_H
