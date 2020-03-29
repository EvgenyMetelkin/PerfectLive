#ifndef CHARTOFEARNED_H
#define CHARTOFEARNED_H

#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class ChartOfEarned
{
    Q_OBJECT
public:
    ChartOfEarned();
    ~ChartOfEarned();

    QChartView* getChart();

private:
    QChartView *chartView;
};

#endif // CHARTOFEARNED_H
