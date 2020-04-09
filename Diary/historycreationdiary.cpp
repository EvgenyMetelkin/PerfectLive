#include "historycreationdiary.h"

#include <QtCore/QtMath>
#include <QtCore/QDebug>

QT_CHARTS_USE_NAMESPACE

#include <QDebug>

HistoryCreationDiary::HistoryCreationDiary(QWidget *parent)
    : QChartView(new QChart(), parent),
      m_scatter(nullptr),
      m_scatter2(nullptr)
{
    setRenderHint(QPainter::Antialiasing);

    this->setMinimumSize(900, 170);
    //this->setMaximumSize(900, 170);

    m_scatter = new QScatterSeries();
    m_scatter->setColor(QColor("#e0e0e0"));

    qreal offset = 0.5;
    int countWeek = 52, countDayOnWeek = 7;
    int i = 0, j = 0;
    for (qreal x(offset); i < countWeek; x += 1.0, ++i) {
        for (qreal y(offset); j < countDayOnWeek; y += 1.0, ++j) {
            *m_scatter << QPointF(x, y);
        }
        j = 0;
    }
    m_scatter2 = new QScatterSeries();

    chart()->addSeries(m_scatter2);
    chart()->addSeries(m_scatter);
    chart()->createDefaultAxes();
    chart()->axes(Qt::Horizontal).first()->setRange(0, countWeek);
    chart()->axes(Qt::Vertical).first()->setRange(0, countDayOnWeek);
    chart()->axisX()->hide();
    chart()->axisY()->hide();
    chart()->legend()->hide();
}

HistoryCreationDiary::~HistoryCreationDiary()
{
    delete m_scatter;
    delete m_scatter2;
}


