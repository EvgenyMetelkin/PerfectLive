#include "modifyfile.h"
#include "ui_modifyfile.h"

#include <QDebug>

ModifyFile::ModifyFile(QString &_dir, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyFile),
    dir(_dir),
    file(_dir)
{
    ui->setupUi(this);
    qDebug() << "Open " << dir;
    openFile();
    this->show();
}

ModifyFile::~ModifyFile() // !? не вызывается диструктор если нажать на крест
{
    file.close();
    qDebug() << "Close " << dir;
    delete ui;
}

void ModifyFile::openFile()
{
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Don't open file...";
        return;
    }

    QTextStream in(&file);
    ui->text->setPlainText(in.readAll());
}

void ModifyFile::on_bSaveChanges_clicked()
{
    QTextStream out(&file);
    out << ui->text->toPlainText();
    delete this;
}

void ModifyFile::on_ModifyFile_destroyed()
{
    delete this;
}
