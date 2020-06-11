#ifndef DBCENSUS_H
#define DBCENSUS_H

#include <QObject>
#include <QSqlDatabase>
#include <QVariantList>
#include <QStringList>

#define TABLE_CENSUS    "census"

class DBCensus : public QObject
{
    Q_OBJECT
public:
    explicit DBCensus(QObject *parent = 0);
    ~DBCensus();

    bool inserIntoCensus(const QVariantList &data);
    QStringList getNameColumn();

private:
    bool openDBCensus();
    void closeDBCensus();
    bool createTableIfNotExists();

private:
};

#endif // DBCENSUS_H
