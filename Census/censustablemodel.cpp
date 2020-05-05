#include "censustablemodel.h"

CensusTableModel::CensusTableModel()
{
    SetupModel();
}

void CensusTableModel::SetupModel()
{
    model.setTable(TABLE_CENSUS);

    int i = 0;
    for(QString nameColumn : dbCensus.GetNameColumn()){
        model.setHeaderData(i++, Qt::Horizontal, nameColumn);
    }
    // Устанавливаем сортировку по возрастанию даты
    model.setSort(1,Qt::AscendingOrder);
}

void CensusTableModel::InserIntoCensus(const QVariantList &data)
{
    dbCensus.InserIntoCensus(data);
}

QSqlTableModel* CensusTableModel::GetTableModel()
{
    model.select(); // Делаем выборку данных из таблицы
    return &model;
}
