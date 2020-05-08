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

    bool InserIntoCensus(const QVariantList &data);
    QStringList GetNameColumn();

private:
    bool OpenDBCensus();
    void CloseDBCensus();
    bool CreateTableIfNotExists();

private:
    //QSqlDatabase    db;
};

#endif // DBCENSUS_H
