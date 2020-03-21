#include "openoldfilewidget.h"
#include "ui_openoldfilewidget.h"

#include <QDebug>

FileButton::FileButton(QString &_path, QWidget *parent)
    : QPushButton(parent)
{
    path = _path;
    connect(this, &FileButton::clicked, this, &FileButton::clickFileButton);
}

void FileButton::clickFileButton()
{
    emit signalOpenFile(path);
}

///////////////////////////////////////////////////////

OpenOldFileWidget::OpenOldFileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenOldFileWidget)
{
    ui->setupUi(this);
}

OpenOldFileWidget::~OpenOldFileWidget() // !? не вызывается диструктор если нажать на крест
{
    foreach(auto btn, listFileButton)
        delete btn;
    delete ui;
}

void OpenOldFileWidget::onShowOpenOldFileWidget(QDir &dir)
{
    listFiles.clear();
    foreach (auto btn, listFileButton) {
        delete btn;
    }
    listFileButton.clear();
    findFile(dir);
    appendListFilesToWidget();
    this->show();
}

void OpenOldFileWidget::findFile(QDir &dir)
{
    QStringList listDirs = dir.entryList(QDir::Dirs |
                                         QDir::AllDirs |
                                         QDir::NoDotAndDotDot);

    QStringList bufListFiles = dir.entryList(QDir::Files);
    QString absolutePath = dir.absolutePath();
    foreach(QString file, bufListFiles)
        listFiles.append(absolutePath + "/" + file);

    //Для папок делаем рекурсивный вызов
    foreach (QString entry, listDirs) {
        QString entryAbsPath = dir.absolutePath() + "/" + entry;
        QDir dr(entryAbsPath);
        findFile(dr);
    }
}

void OpenOldFileWidget::appendListFilesToWidget()
{
    foreach (QString file, listFiles) {
        FileButton *btn = new FileButton(file);
        listFileButton.append(btn);
        btn->setText(file);
        connect(btn, &FileButton::signalOpenFile, this, &OpenOldFileWidget::signalOpenFile);
        ui->fileLayout->addWidget(btn);
    }
}

void OpenOldFileWidget::on_cancel_clicked()
{
    this->hide();
}
