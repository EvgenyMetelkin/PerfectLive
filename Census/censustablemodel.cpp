#include "censustablemodel.h"

CensusTableModel::CensusTableModel()
{
    SetupModel();
}

void CensusTableModel::SetupModel()
{
    m_model.setTable(TABLE_CENSUS);

    int i = 0;
    for(QString nameColumn : m_dbCensus.GetNameColumn()){
        m_model.setHeaderData(i++, Qt::Horizontal, nameColumn);
    }
    // Устанавливаем сортировку по возрастанию даты
    m_model.setSort(1,Qt::AscendingOrder);
}

void CensusTableModel::InserIntoCensus(const QVariantList &data)
{
    m_dbCensus.InserIntoCensus(data);
}

QSqlTableModel* CensusTableModel::GetTableModel()
{
    m_model.select(); // Делаем выборку данных из таблицы
    return &m_model;
}
