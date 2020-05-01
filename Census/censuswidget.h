#ifndef CENSUSWIDGET_H
#define CENSUSWIDGET_H

#include <QWidget>

namespace Ui {
class CensusWidget;
}

class CensusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CensusWidget(QWidget *parent = nullptr);
    ~CensusWidget();

private slots:
    void LoadFromDB();

    void on_cofMe_valueChanged(double arg1);
    void on_cofArtist_valueChanged(double arg1);
    void on_fact_editingFinished();
    void on_rate_editingFinished();

private:
    void CalculateValues();

private:
    Ui::CensusWidget *ui;
};

#endif // CENSUSWIDGET_H
