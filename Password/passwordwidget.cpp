#include "passwordwidget.h"
#include "ui_passwordwidget.h"

#include <QDebug>
#include <Global/settings.h>
#include <Global/filedirutils.h>

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

bool PasswordWidget::checkPass(const QString &pass)
{
    QString hash = FileDirUtils::getMD5(pass);

    if(hash == "00a1f187721c63501356bf791e69382c") {
        Settings::set(Settings::Mode, Settings::General) = "base";
        return true;
    } else if(hash == "f76c5fb89441d68e9bb15929f0a7e533") {
        Settings::set(Settings::Mode, Settings::General) = "hidden";
        return true;
    }
    return false;
}

void PasswordWidget::on_Accept_clicked()
{
    qDebug() << Settings::get(Settings::Mode, Settings::General).toString();

    if(checkPass(ui->Password->text())) {
        emit confirmedPassword();
    } else {
        ui->Error->setText("Failed password");
    }
}

void PasswordWidget::on_Password_textChanged(const QString &text)
{
    ui->Error->setText("");
    if(text == "")
        ui->Accept->setEnabled(false);
    else
        ui->Accept->setEnabled(true);
}
