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
    QBarSet set0;
    QBarSet set1;
    QBarSet set2;
    QBarSet set3;
    QBarSet set4;
    QStackedBarSeries series;
    QChart chart;
    QBarCategoryAxis axisX;
    QValueAxis axisY;
};

#endif // INCOMEVIEW_H
