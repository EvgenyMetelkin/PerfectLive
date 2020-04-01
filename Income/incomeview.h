#ifndef INCOMEVIEW_H
#define INCOMEVIEW_H

#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class IncomeView : public QObject
{
public:
    explicit IncomeView(QWidget *parent = nullptr);
    ~IncomeView();

    QChartView* GetIncomeView();

private:
    void CreateChart();

private:
    QChartView *m_incomeView;
};

#endif // INCOMEVIEW_H
