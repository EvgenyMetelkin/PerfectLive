#ifndef DBCENSUS_H
#define DBCENSUS_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>


class DBCensus : public QObject
{
    Q_OBJECT
public:
    explicit DBCensus(QObject *parent = 0);
    ~DBCensus();

    bool InserIntoTable(const QVariantList &data);

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

private:
    bool CreateTableIfNotExists();
    bool RestoreDBCensus();
    void CloseDBCensus();
};

#endif // DBCENSUS_H
