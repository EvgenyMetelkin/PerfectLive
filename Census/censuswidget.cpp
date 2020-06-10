#include "censuswidget.h"
#include "ui_censuswidget.h"

#include <QDebug>

CensusWidget::CensusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CensusWidget)
{
    ui->setupUi(this);

    connect(this, &QWidget::show, this, &CensusWidget::LoadFromDB);
}

CensusWidget::~CensusWidget()
{
    delete ui;
}

void CensusWidget::SetModel()
{
    ui->tableView->setModel(m_tableModel.GetTableModel());
    //ui->tableView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

void CensusWidget::LoadFromDB()
{
    qDebug() << Q_FUNC_INFO;
}

void CensusWidget::CalculateValues()
{
    double countUSD = ui->fact->value();

    double toMeUSD = countUSD * ui->cofMe->value();
    double toArtistUSD = countUSD * ui->cofArtist->value();
    ui->toMeUSD->setText(QString::number(toMeUSD));
    ui->toArtistUSD->setText(QString::number(toArtistUSD));

    double rate = ui->rate->value();
    double toMeRub = toMeUSD * rate;
    double toArtistRub = toArtistUSD * rate;
    ui->toMeRub->setText(QString::number(toMeRub));
    ui->toArtistRub->setText(QString::number(toArtistRub));
}

void CensusWidget::on_cofMe_valueChanged(double value)
{
    ui->cofArtist->setValue(1 - value);
    CalculateValues();
}

void CensusWidget::on_cofArtist_valueChanged(double value)
{
    ui->cofMe->setValue(1 - value);
    CalculateValues();
}

void CensusWidget::on_fact_editingFinished()
{
    CalculateValues();
}


void CensusWidget::on_rate_editingFinished()
{
    CalculateValues();
}
