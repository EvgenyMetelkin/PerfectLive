#include "passwordwidget.h"
#include "ui_passwordwidget.h"

#include <QDebug>

PasswordWidget::PasswordWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordWidget)
{
    ui->setupUi(this);
}

PasswordWidget::~PasswordWidget()
{
    delete ui;
}

void PasswordWidget::on_Accept_clicked()
{
    if(ui->Password->text() == "12344321")
        emit confirmedBasePassword();
    else if(ui->Password->text() == "zkexibq4")
        emit confirmedMainPassword();
    else
        ui->Error->setText("Failed password");
}

void PasswordWidget::on_Password_textChanged(const QString &text)
{
    ui->Error->setText("");
    if(text == "")
        ui->Accept->setEnabled(false);
    else
        ui->Accept->setEnabled(true);
}
