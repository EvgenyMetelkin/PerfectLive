#ifndef DBHISTORYDIARY_H
#define DBHISTORYDIARY_H

#include <QObject>
#include <QSqlDatabase>

class DBHistoryDiary : public QObject
{
    Q_OBJECT
public:
    explicit DBHistoryDiary(QObject *parent = nullptr);

    void ConnectToDataBase();
    bool InsertHistoryDiary(const int value);
    void SelectAllHistoryDiary();
    void SelectYearFromHistoryDiary();

signals:
    void ReplyForSelect(QString date, int value);

private:
    bool OpenDataBase();
    void CloseDataBase();
    bool CreateTableIfNotExists();

private:
    QSqlDatabase db;
};

#endif // DBHISTORYDIARY_H
