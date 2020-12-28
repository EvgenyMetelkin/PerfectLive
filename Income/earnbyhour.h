#ifndef EARNBYHOUR_H
#define EARNBYHOUR_H

#include <QStringList>

class EarnByHour
{
public:
    EarnByHour();

    void create(QStringList &m_sumIncome);
    QString getTotalIncome();
    QString getEarnByHour();

private:
    int calculateCountHour(int currentMount);

private:
    int m_totalIncome;
    float m_earnByHour;
};

#endif // EARNBYHOUR_H
