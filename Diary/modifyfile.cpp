#include "modifyfile.h"
#include "ui_modifyfile.h"
#include "Global/settings.h"

#include <QDebug>

ModifyFile::ModifyFile(QString &_dir, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyFile),
    m_dir(_dir),
    m_file(_dir)
{
    ui->setupUi(this);
    qDebug() << "Open " << m_dir;
    OpenFile();
    this->show();
}

ModifyFile::~ModifyFile() // !! не вызывается диструктор если нажать на крест
{
    m_file.close();
    qDebug() << "Close " << m_dir;
    delete ui;
}

void ModifyFile::OpenFile()
{
    if (!m_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Don't open file...";
        return;
    }

    QTextStream in(&m_file);

    if(Settings::get(Settings::Mode, Settings::General).toString() != "hidden")
        ui->text->setPlainText(DoNotReadHiddenLine(in));
    else
        ui->text->setPlainText(in.readAll());

}

QString ModifyFile::DoNotReadHiddenLine(QTextStream &in)
{
    QString textWithoutHiddenLine;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(!line.startsWith("    //") || !line.startsWith("//"))
            textWithoutHiddenLine += line + "\n";
    }
    return textWithoutHiddenLine;
}

void ModifyFile::on_bSaveChanges_clicked()
{
    QTextStream out(&m_file);
    out << ui->text->toPlainText();
    delete this;
}

void ModifyFile::on_ModifyFile_destroyed()
{
    delete this;
}
