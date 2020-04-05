#ifndef INCOMEVIEW_H
#define INCOMEVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

class IncomeView : public QChartView
{
public:
    explicit IncomeView(QWidget *parent = nullptr);
    ~IncomeView();

private:
    void Initialize();
    void CreateChart();

private:
    QChartView *m_incomeView;
    QBarSet m_setSalary;
    QBarSet m_setFA;
    QBarSet m_setAlimony;
    QBarSet m_setPassiveIncome;
    QBarSet m_setOther;
    QStackedBarSeries m_series;
    QChart m_chart;
    QBarCategoryAxis m_axisX;
    QValueAxis m_axisY;
    int m_countMount;
};

#endif // INCOMEVIEW_H
