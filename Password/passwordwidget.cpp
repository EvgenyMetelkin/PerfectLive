#include "passwordwidget.h"
#include "ui_passwordwidget.h"

#include <QDebug>
#include <Global/settings.h>

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
    qDebug() << Settings::get(Settings::Mode, Settings::General).toString();
    if(ui->Password->text() == "12344321") {
        Settings::set(Settings::Mode, Settings::General) = "base";
        emit confirmedPassword();
    }
    else if(ui->Password->text() == "zkexibq4") {
        Settings::set(Settings::Mode, Settings::General) = "hidden";
        emit confirmedPassword();
    }
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
