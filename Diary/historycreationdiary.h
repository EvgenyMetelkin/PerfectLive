#ifndef HISTORYCREATIONDIARY_H
#define HISTORYCREATIONDIARY_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>

QT_CHARTS_USE_NAMESPACE

class HistoryCreationDiary : public QChartView
{
    Q_OBJECT

public:
    HistoryCreationDiary(QWidget *parent = nullptr);
    ~HistoryCreationDiary();

private:
    QScatterSeries *m_scatter;
    QScatterSeries *m_scatter2;
};

#endif // HISTORYCREATIONDIARY_H
