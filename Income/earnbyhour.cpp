#include "earnbyhour.h"

#include <QDebug>
#include <QDate>

EarnByHour::EarnByHour() :
    m_totalIncome(0),
    m_earnByHour(0)
{}

void EarnByHour::create(QStringList &m_sumIncome)
{
    m_totalIncome = 0;
    for(auto incomeInMount : m_sumIncome) {
        m_totalIncome += incomeInMount.toInt();
    }

    if(m_sumIncome.length() > 0)
        m_earnByHour = m_totalIncome / calculateCountHour(m_sumIncome.length());
    else
        qDebug() << Q_FUNC_INFO << "Earn file empty!";
}

QString EarnByHour::getTotalIncome()
{
    return QString::number(m_totalIncome);
}

QString EarnByHour::getEarnByHour()
{
    return QString::number(m_earnByHour);
}

qint64 EarnByHour::calculateCountHour(int currentMount)
{
    QDate currentDate = QDate::currentDate();
    QDate firstOfJanuaryDate(currentDate.year(), 1, 1);
    QDate lastDayLastMountDate;

    // получаем последнее число текущего месяца
    lastDayLastMountDate = QDate(currentDate.year(), currentMount, 1);
    lastDayLastMountDate = lastDayLastMountDate.addMonths(1);
    lastDayLastMountDate = lastDayLastMountDate.addDays(-1);

    return firstOfJanuaryDate.daysTo(lastDayLastMountDate) * 24;
}
