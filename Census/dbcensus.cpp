#include "dbcensus.h"

#include "../Global/filedirutils.h"

#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#define TABLE                   "census"
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

void DBCensus::CloseDBCensus()
{
    db.close();
}

bool DBCensus::CreateTableIfNotExists()
{
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE IF NOT EXISTS " TABLE " ("
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
        qDebug() << Q_FUNC_INFO << "DataBase: error of create " << TABLE;
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool DBCensus::InserIntoCensus(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE " ( " TABLE_DATE ", "
                  TABLE_MAST_BE  ", " TABLE_FACT ", " TABLE_ME_USD ", "
                  TABLE_ARTIST_USD ", " TABLE_ME_RUB ", " TABLE_ARTIST_RUB ", "
                  TABLE_RATE ", " TABLE_ARTIST ", " TABLE_FOR_WHAT " ) "
                  "VALUES (date('now','localtime'), :mastBe, :fact, :meUSD, :artistUSD,"
                  ":meRub, :artistRub, :rate, :artist, :forWhat )");
//    query.bindValue(":mastBe", mastBe);
//    query.bindValue(":fact", fact);
//    query.bindValue(":meUSD", meUSD);
//    query.bindValue(":artistUSD", artistUSD);
//    query.bindValue(":meRub", meRub);
//    query.bindValue(":artistRub", artistRub);
//    query.bindValue(":rate", rate);
//    query.bindValue(":artist", artist);
//    query.bindValue(":forWhat", forWhat);

    if(!query.exec()) {
        qDebug() << Q_FUNC_INFO << "error insert into " << TABLE;
        qDebug() << Q_FUNC_INFO << query.lastError().text();
        return false;
    } else {
        return true;
    }
}
