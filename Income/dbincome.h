#ifndef DBINCOME_H
#define DBINCOME_H

#include <QObject>

class DBIncome : public QObject
{
    Q_OBJECT
public:
    explicit DBIncome(QObject *parent = nullptr);

    bool InsertNewMount(const int value);
    void SelectCountMount();
    void SelectAllIncome();

private:
    bool OpenDataBase();
    void CloseDataBase();
    bool CreateTableIfNotExists();
};

#endif // DBINCOME_H
