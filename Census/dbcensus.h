#ifndef DBCENSUS_H
#define DBCENSUS_H

#include <QObject>
#include <QSqlDatabase>

class DBCensus : public QObject
{
    Q_OBJECT
public:
    explicit DBCensus(QObject *parent = nullptr);
    ~DBCensus();

    bool InserIntoCensus(const QVariantList &data);

private:
    bool OpenDBCensus();
    void CloseDBCensus();
    bool CreateTableIfNotExists();

private:
    QSqlDatabase    db;
};

#endif // DBCENSUS_H
