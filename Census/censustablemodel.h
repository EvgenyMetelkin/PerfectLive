#ifndef CENSUSTABLEMODEL_H
#define CENSUSTABLEMODEL_H

#include "dbcensus.h"

#include <QSqlTableModel>

class CensusTableModel
{

public:
    CensusTableModel();

    void inserIntoCensus(const QVariantList &data);
    QSqlTableModel* getTableModel();

private:
    void setupModel();

private:
    QSqlTableModel m_model;
    DBCensus m_dbCensus;
};

#endif // CENSUSTABLEMODEL_H
