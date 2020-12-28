#include "earnbyhour.h"

#include <QDebug>
#include <QDate>

EarnByHour::EarnByHour() :
    m_totalIncome(0),
    m_earnByHour(0)
{}

void EarnByHour::create(QStringList &m_sumIncome)
{
    int m_totalIncome = 0;
    for(auto incomeInMount : m_sumIncome) {
        m_totalIncome += incomeInMount.toInt();
    }

    //calculateCountHour(m_sumIncome.length());
}

QString EarnByHour::getTotalIncome()
{
    return QString::number(m_totalIncome);
}

QString EarnByHour::getEarnByHour()
{
    return QString::number(m_earnByHour);
}

int EarnByHour::calculateCountHour(int currentMount)
{
    QDate currentDate = QDate::currentDate();
    QDate firstOfJanuaryDate(currentDate.year(), 1, 1);
    QDate lastDayLastMountDate;

    if(currentMount < 12) {
        lastDayLastMountDate = QDate(currentDate.year(), currentMount, 1);
        lastDayLastMountDate = lastDayLastMountDate.addDays(-1);
    } else if(currentMount == 12) {
        lastDayLastMountDate = QDate(currentDate.year(), 12, 31);
    } else {
        qDebug() << "Error count mount " << currentMount;
        return -4;
    }

    qDebug() << currentMount << " currentDate " << currentDate << endl << "firstOfJanuaryDate " << firstOfJanuaryDate << endl << "lastDayLastMountDate " << lastDayLastMountDate;


}
