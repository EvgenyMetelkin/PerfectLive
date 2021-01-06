#ifndef INCOMEVIEW_H
#define INCOMEVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

#include "earnbyhour.h"

#include <QTextStream>

class IncomeView : public QChartView
{
public:
    explicit IncomeView(QWidget *parent = nullptr);
    ~IncomeView();

    QString getTotalIncome();
    QString getEarnByHour();

private:
    void initialize();
    void openEarnFile();
    void createEarnFile();
    void createChart();
    void createEarnByHour();

private:
    QChartView *m_incomeView;
    QFile m_earnFile;

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
    QStringList m_sumIncome;

    EarnByHour m_earnByHour;
};

#endif // INCOMEVIEW_H
