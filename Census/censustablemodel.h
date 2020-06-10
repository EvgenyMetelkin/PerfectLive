#ifndef CENSUSTABLEMODEL_H
#define CENSUSTABLEMODEL_H

#include "dbcensus.h"

#include <QSqlTableModel>

class CensusTableModel
{

public:
    CensusTableModel();

    void InserIntoCensus(const QVariantList &data);
    QSqlTableModel* GetTableModel();

private:
    void SetupModel();

private:
    QSqlTableModel m_model;
    DBCensus m_dbCensus;
};

#endif // CENSUSTABLEMODEL_H
