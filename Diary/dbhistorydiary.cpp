#include "dbhistorydiary.h"

#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>

#include "../Global/filedirutils.h"

#define DATABASE_HOSTNAME   "PerfectLive"
#define DATABASE_NAME       "PerfectLive.db"

#define TABLE               "historyDiary"
#define TABLE_DATE          "date"
#define TABLE_VALUE         "value"

DBHistoryDiary::DBHistoryDiary(QObject *parent) : QObject(parent)
{
    OpenDataBase();
}

bool DBHistoryDiary::OpenDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(FileDirUtils::GetCurrentPath() + DATABASE_NAME); // !! помести базу в ресурсы
    CreateTableIfNotExists();
    if(db.open()){
        return true;
    } else {
        return false;
    }
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
                    TABLE_DATE      " DATE            NOT NULL,"
                    TABLE_VALUE     " INTEGER         NOT NULL"
                    " )"
                    )) {
        qDebug() << Q_FUNC_INFO << "DataBase: error of create " << TABLE;
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool DBHistoryDiary::InserIntoTable(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE " ( " TABLE_DATE ", "
                  TABLE_VALUE " ) "
                  "VALUES (:date, :value)");
    query.bindValue(":date",        data[0].toDate());
    query.bindValue(":value",       data[1].toInt());
    if(!query.exec()) {
        qDebug() << Q_FUNC_INFO << "error insert into " << TABLE;
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return false;
    } else {
        return true;
    }
}
