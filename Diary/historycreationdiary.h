#ifndef HISTORYCREATIONDIARY_H
#define HISTORYCREATIONDIARY_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QDate>

QT_CHARTS_USE_NAMESPACE

class HistoryCreationDiary : public QChartView
{
    Q_OBJECT

public:
    HistoryCreationDiary(QWidget *parent = nullptr);
    ~HistoryCreationDiary();

private slots:
    void replyForSelectYear(QString date, int value);
    void handleClickedPoint(const QPointF &point);

private:
    void loadHistoryDiary();
    int getTargetDay(const QString &date);
    void markOfDay(int targetDay, int value);

private:
    QScatterSeries *m_scatter;
    QScatterSeries *m_scatter1;
    QScatterSeries *m_scatter2;
    QScatterSeries *m_scatter3;
    QScatterSeries *m_scatter4;

    int c_current_day;
    QDate c_current_date;
    int c_countPoints;
};

#endif // HISTORYCREATIONDIARY_H
