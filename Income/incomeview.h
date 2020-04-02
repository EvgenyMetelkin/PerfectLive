#ifndef INCOMEVIEW_H
#define INCOMEVIEW_H

#include <QList>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>

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
    QList<QBarSet*> m_listBarSet;
    QBarSet set0;
};

#endif // INCOMEVIEW_H
