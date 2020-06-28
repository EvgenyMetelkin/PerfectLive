#include "historycreationdiary.h"

#include <QtCore/QtMath>
#include <QtCore/QDebug>

QT_CHARTS_USE_NAMESPACE

#include <QDate>
#include <QDebug>

#include "dbhistorydiary.h"

#define COUNT_WEEK 52
#define COUNT_DAY_ON_WEEK 7

HistoryCreationDiary::HistoryCreationDiary(QWidget *parent)
    : QChartView(new QChart(), parent),
      m_scatter(new QScatterSeries(this)),
      m_scatter1(new QScatterSeries(this)),
      m_scatter2(new QScatterSeries(this)),
      m_scatter3(new QScatterSeries(this)),
      m_scatter4(new QScatterSeries(this))
{
    c_current_date = QDate::currentDate();
    c_current_day = c_current_date.dayOfWeek();

    setRenderHint(QPainter::Antialiasing);

    this->setMinimumSize(900, 170);

    m_scatter->setColor(QColor("#e0e0e0"));
    m_scatter1->setColor(QColor("#a7d984"));
    m_scatter2->setColor(QColor("#5da130"));
    m_scatter3->setColor(QColor("#F6A625"));
    m_scatter4->setColor(QColor("#BF593E"));

    qreal offset = 0.5;
    int i = 0, j = 0;
    for (qreal x(offset); i < COUNT_WEEK - 1; x += 1.0, ++i) {
        for (qreal y(COUNT_DAY_ON_WEEK - offset); j < COUNT_DAY_ON_WEEK; y -= 1.0, ++j) {
            *m_scatter << QPointF(x, y);
        }
        j = 0;
    }
    // для последней недели особое добавление
    j = 0;
    for (qreal x(COUNT_WEEK - offset), y(COUNT_DAY_ON_WEEK - offset); j < c_current_day; y -= 1.0, ++j) {
        *m_scatter << QPointF(x, y);
    }
    c_countPoints = m_scatter->points().size();

    chart()->addSeries(m_scatter);
    chart()->addSeries(m_scatter1);
    chart()->addSeries(m_scatter2);
    chart()->addSeries(m_scatter3);
    chart()->addSeries(m_scatter4);

    chart()->createDefaultAxes();
    chart()->axes(Qt::Horizontal).first()->setRange(0, COUNT_WEEK);
    chart()->axes(Qt::Vertical).first()->setRange(0, COUNT_DAY_ON_WEEK);
    chart()->axisX()->hide();
    chart()->axisY()->hide();
    chart()->legend()->hide();

    loadHistoryDiary();
    connect(m_scatter1, &QScatterSeries::clicked, this, &HistoryCreationDiary::handleClickedPoint);
}

HistoryCreationDiary::~HistoryCreationDiary()
{
}

void HistoryCreationDiary::loadHistoryDiary()
{
    DBHistoryDiary db(this);
    connect(&db, &DBHistoryDiary::ReplyForSelect, this, &HistoryCreationDiary::replyForSelectYear);
    db.SelectYearFromHistoryDiary();
}

void HistoryCreationDiary::replyForSelectYear(QString date, int value) // [slot]
{
    qDebug() << Q_FUNC_INFO << date << " " << value;
    markOfDay(getTargetDay(date), value);
}

int HistoryCreationDiary::getTargetDay(const QString &dateString)
{
    QDate date = QDate::fromString(dateString, "yyyy-MM-dd");
    return (c_countPoints - static_cast<int>(date.daysTo(c_current_date))) - 1;
}

// правильно работает только если отмечать дни по убыванию даты
void HistoryCreationDiary::markOfDay(int targetDay, int value)
{
    if(targetDay < 0) {
        qDebug() << Q_FUNC_INFO << "Error: target day more count day";
        return;
    }

    QPointF targetPoint = m_scatter->points().at(targetDay);

    m_scatter->remove(targetPoint);

    switch (value) {
    case 1:
        m_scatter1->append(targetPoint);
        break;
    case 2:
        m_scatter2->append(targetPoint);
        break;
    case 3:
        m_scatter3->append(targetPoint);
        break;
    case 4:
        m_scatter4->append(targetPoint);
        break;
    }
}

void HistoryCreationDiary::handleClickedPoint(const QPointF &point)
{
    //QPointF clickedPoint = point;
    qDebug() << "point" << point;
    // Find the closest point from series 1
//    QPointF closest(INT_MAX, INT_MAX);
//    qreal distance(INT_MAX);
//    const auto points = m_scatter->points();
//    for (const QPointF &currentPoint : points) {
//        qreal currentDistance = qSqrt((currentPoint.x() - clickedPoint.x())
//                                      * (currentPoint.x() - clickedPoint.x())
//                                      + (currentPoint.y() - clickedPoint.y())
//                                      * (currentPoint.y() - clickedPoint.y()));
//        if (currentDistance < distance) {
//            distance = currentDistance;
//            closest = currentPoint;
//        }
//    }

//    // Remove the closes point from series 1 and append it to series 2
//    m_scatter->remove(closest);
//    m_scatter2->append(closest);
}
