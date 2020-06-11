#include "censustablemodel.h"

CensusTableModel::CensusTableModel()
{
    setupModel();
}

void CensusTableModel::setupModel()
{
    m_model.setTable(TABLE_CENSUS);

    int i = 0;
    for(QString nameColumn : m_dbCensus.getNameColumn()){
        m_model.setHeaderData(i++, Qt::Horizontal, nameColumn);
    }
    // Устанавливаем сортировку по возрастанию даты
    m_model.setSort(1,Qt::AscendingOrder);
}

void CensusTableModel::inserIntoCensus(const QVariantList &data)
{
    m_dbCensus.inserIntoCensus(data);
}

QSqlTableModel* CensusTableModel::getTableModel()
{
    m_model.select(); // Делаем выборку данных из таблицы
    return &m_model;
}
