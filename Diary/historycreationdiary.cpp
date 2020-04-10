#include "historycreationdiary.h"

#include <QtCore/QtMath>
#include <QtCore/QDebug>

QT_CHARTS_USE_NAMESPACE

#include <QDebug>

#define COUNT_WEEK 52
#define COUNT_DAY_ON_WEEK 7

HistoryCreationDiary::HistoryCreationDiary(QWidget *parent)
    : QChartView(new QChart(), parent),
      m_scatter(nullptr),
      m_scatter2(nullptr)
{
    setRenderHint(QPainter::Antialiasing);

    this->setMinimumSize(900, 170);

    m_scatter = new QScatterSeries();
    m_scatter->setColor(QColor("#e0e0e0"));

    qreal offset = 0.5;
    int i = 0, j = 0;
    for (qreal x(offset); i < COUNT_WEEK; x += 1.0, ++i) {
        for (qreal y(COUNT_DAY_ON_WEEK - offset); j < COUNT_DAY_ON_WEEK; y -= 1.0, ++j) {
            *m_scatter << QPointF(x, y);
        }
        j = 0;
    }
    m_scatter2 = new QScatterSeries();

    chart()->addSeries(m_scatter2);
    chart()->addSeries(m_scatter);
    chart()->createDefaultAxes();
    chart()->axes(Qt::Horizontal).first()->setRange(0, COUNT_WEEK);
    chart()->axes(Qt::Vertical).first()->setRange(0, COUNT_DAY_ON_WEEK);
    chart()->axisX()->hide();
    chart()->axisY()->hide();
    chart()->legend()->hide();

    MarkOfDay(1,1);

    MarkOfDay(51,0);
}

HistoryCreationDiary::~HistoryCreationDiary()
{
    delete m_scatter;
    delete m_scatter2;
}

void HistoryCreationDiary::MarkOfDay(int week, int day)
{
    int targetDay = week * COUNT_DAY_ON_WEEK + day;

    QPointF targetPoint = m_scatter->points().at(targetDay);

    m_scatter->remove(targetPoint);
    m_scatter2->append(targetPoint);
}
