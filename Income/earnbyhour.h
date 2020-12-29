#ifndef EARNBYHOUR_H
#define EARNBYHOUR_H

#include <QStringList>

///
/// \brief The EarnByHour class
/// Считает общий доход за год
/// и сколько было заработанно за каждый час
///
class EarnByHour
{
public:
    EarnByHour();

    void create(QStringList &m_sumIncome);
    QString getTotalIncome();
    QString getEarnByHour();

private:
    ///
    /// \brief calculateCountHour
    /// \param currentMount - номер последнего месяца
    /// \return - кол-во часов от начала года до последнего часа последнего месяца
    ///
    qint64 calculateCountHour(int currentMount);

private:
    int m_totalIncome;
    double m_earnByHour;
};

#endif // EARNBYHOUR_H
