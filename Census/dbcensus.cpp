#include "dbcensus.h"

#include "../Global/filedirutils.h"

#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#define TABLE_DATE              "Date"
#define TABLE_MAST_BE           "MastBe"
#define TABLE_FACT              "Fact"
#define TABLE_ME_USD            "ToMeUSD"
#define TABLE_ARTIST_USD        "ToArtistUSD"
#define TABLE_ME_RUB            "ToMeRub"
#define TABLE_ARTIST_RUB        "ToArtistRub"
#define TABLE_RATE              "Rate"
#define TABLE_ARTIST            "Artist"
#define TABLE_FOR_WHAT          "ForWhat"

#define DATABASE_d   "PerfectLive"
#define DATABASE_c      "Census.db"


DBCensus::DBCensus(QObject *parent) : QObject(parent)
{
    OpenDBCensus();
}

DBCensus::~DBCensus()
{
    CloseDBCensus();
}

bool DBCensus::OpenDBCensus()
{
    //db = QSqlDatabase::addDatabase("QSQLITE"); // ! перекомпилить sqlite для 64-бит
    db.setHostName(DATABASE_d);
    db.setDatabaseName(DATABASE_c);
    CreateTableIfNotExists();
    if(!db.open()){
        qDebug() << Q_FUNC_INFO << "Don't open db " DATABASE_c;
        return false;
    }
    return true;
}

void DBCensus::CloseDBCensus()
{
    db.close();
}

bool DBCensus::CreateTableIfNotExists()
{
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE IF NOT EXISTS " TABLE_CENSUS " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE_DATE       " DATE            NOT NULL      UNIQUE,"
                    TABLE_MAST_BE    " REAL            NOT NULL      ,"
                    TABLE_FACT       " REAL            NOT NULL      ,"
                    TABLE_ME_USD     " REAL            NOT NULL      ,"
                    TABLE_ARTIST_USD " REAL            NOT NULL      ,"
                    TABLE_ME_RUB     " REAL            NOT NULL      ,"
                    TABLE_ARTIST_RUB " REAL            NOT NULL      ,"
                    TABLE_RATE       " REAL            NOT NULL      ,"
                    TABLE_ARTIST     " TEXT            NOT NULL      ,"
                    TABLE_FOR_WHAT   " TEXT            NOT NULL      "
                    " )"
                    )) {
        qDebug() << Q_FUNC_INFO << "DataBase: error of create " << TABLE_CENSUS;
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool DBCensus::InserIntoCensus(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE_CENSUS " ( " TABLE_DATE ", "
                  TABLE_MAST_BE  ", " TABLE_FACT ", " TABLE_ME_USD ", "
                  TABLE_ARTIST_USD ", " TABLE_ME_RUB ", " TABLE_ARTIST_RUB ", "
                  TABLE_RATE ", " TABLE_ARTIST ", " TABLE_FOR_WHAT " ) "
                  "VALUES (date('now','localtime'), :mastBe, :fact, :meUSD, :artistUSD,"
                  ":meRub, :artistRub, :rate, :artist, :forWhat )");
    query.bindValue(":mastBe", data[0].toDouble());
    query.bindValue(":fact", data[1].toDouble());
    query.bindValue(":meUSD", data[2].toDouble());
    query.bindValue(":artistUSD", data[3].toDouble());
    query.bindValue(":meRub", data[4].toDouble());
    query.bindValue(":artistRub", data[5].toDouble());
    query.bindValue(":rate", data[6].toDouble());
    query.bindValue(":artist", data[7].toString());
    query.bindValue(":forWhat", data[8].toString());

    if(!query.exec()) {
        qDebug() << Q_FUNC_INFO << "error insert into " << TABLE_CENSUS;
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

QStringList DBCensus::GetNameColumn()
{
    QStringList res;
    res << "id" << TABLE_DATE << TABLE_MAST_BE << TABLE_FACT << TABLE_ME_USD;
    res << TABLE_ARTIST_USD << TABLE_ME_RUB << TABLE_ARTIST_RUB;
    res << TABLE_RATE << TABLE_ARTIST << TABLE_FOR_WHAT;
    return res;
}
