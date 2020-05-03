#include "dbhistorydiary.h"

#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QDate>

#include "../Global/filedirutils.h"

#define TABLE               "historyDiary"
#define TABLE_DATE          "date"
#define TABLE_VALUE         "value"


DBHistoryDiary::DBHistoryDiary(QObject *parent) :
    QObject(parent)
{
    OpenDataBase();
}

bool DBHistoryDiary::OpenDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE"); // ! перекомпилить sqlite для 64-бит
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    if(!db.open()){
        qDebug() << Q_FUNC_INFO << "Don't open db " DATABASE_NAME;
        return false;
    }
    CreateTableIfNotExists();
    return true;
}

void DBHistoryDiary::CloseDataBase()
{
    db.close();
}

bool DBHistoryDiary::CreateTableIfNotExists()
{
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE IF NOT EXISTS " TABLE " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE_DATE      " DATE            NOT NULL      UNIQUE,"
                    TABLE_VALUE     " INTEGER         NOT NULL      "
                    " )"
                    )) {
        qDebug() << Q_FUNC_INFO << "DataBase: error of create " << TABLE;
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool DBHistoryDiary::InsertHistoryDiary(const int value)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE " ( " TABLE_DATE ", "
                  TABLE_VALUE " ) "
                  "VALUES (date('now','localtime'), :value)");
    query.bindValue(":value", value);

    if(!query.exec()) {
        qDebug() << Q_FUNC_INFO << "error insert into " << TABLE;
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

void DBHistoryDiary::SelectAllHistoryDiary()
{
    QSqlQuery query;
    if(!query.exec( "SELECT * FROM " TABLE " ORDER BY " TABLE_DATE " DESC "
                    )) {
        qDebug() << Q_FUNC_INFO << "DataBase: error of create " << TABLE;
        qDebug() << Q_FUNC_INFO << query.lastError().text();
    }

    while (query.next()) {
        QString date = query.value(1).toString();
        int value = query.value(2).toInt();
        qDebug() << date << value;
    }
}

void DBHistoryDiary::SelectYearFromHistoryDiary()
{
    QDate date(QDate::currentDate().year() - 1, QDate::currentDate().month(), QDate::currentDate().day());
    //qDebug() << Q_FUNC_INFO << "SELECT * FROM " TABLE " WHERE " TABLE_DATE " > " "date('" + date.toString("yyyy-MM-dd") + "')" " ORDER BY " TABLE_DATE " DESC ";

    QSqlQuery query;
    if(!query.exec( "SELECT * FROM " TABLE " WHERE " TABLE_DATE " > " "date('" + date.toString("yyyy-MM-dd") + "')" " ORDER BY " TABLE_DATE " DESC "
                    )) {
        qDebug() << Q_FUNC_INFO << "DataBase: error of create " << TABLE;
        qDebug() << Q_FUNC_INFO << query.lastError().text();
    }

    while (query.next()) {
        QString date = query.value(1).toString();
        int value = query.value(2).toInt();
        emit ReplyForSelect(date, value);
    }
}
