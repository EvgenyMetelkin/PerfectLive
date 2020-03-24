#include "openoldfilewidget.h"
#include "ui_openoldfilewidget.h"

#include <QDebug>

FileButton::FileButton(QString &path, QWidget *parent)
    : QPushButton(parent)
{
    m_path = path;
    connect(this, &FileButton::clicked, this, &FileButton::ClickFileButton);
}

void FileButton::ClickFileButton()
{
    emit SignalOpenFile(m_path);
}

///////////////////////////////////////////////////////

OpenOldFileWidget::OpenOldFileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenOldFileWidget)
{
    ui->setupUi(this);
}

OpenOldFileWidget::~OpenOldFileWidget() // !! не вызывается диструктор если нажать на крест
{
    foreach(auto btn, m_listFileButton)
        delete btn;
    delete ui;
}

void OpenOldFileWidget::OnShowOpenOldFileWidget(QDir &dir)
{
    m_listFiles.clear();
    foreach (auto btn, m_listFileButton) {
        delete btn;
    }
    m_listFileButton.clear();
    FindFile(dir);
    AppendListFilesToWidget();
    this->show();
}

void OpenOldFileWidget::FindFile(QDir &dir) // ! лучше переместить в filedirutils
{
    QStringList listDirs = dir.entryList(QDir::Dirs |
                                         QDir::AllDirs |
                                         QDir::NoDotAndDotDot);

    QStringList bufListFiles = dir.entryList(QDir::Files);
    QString absolutePath = dir.absolutePath();
    foreach(QString file, bufListFiles)
        m_listFiles.append(absolutePath + "/" + file);

    //Для папок делаем рекурсивный вызов
    foreach (QString entry, listDirs) {
        QString entryAbsPath = dir.absolutePath() + "/" + entry;
        QDir dr(entryAbsPath);
        FindFile(dr);
    }
}

void OpenOldFileWidget::AppendListFilesToWidget()
{
    foreach (QString file, m_listFiles) {
        FileButton *btn = new FileButton(file);
        m_listFileButton.append(btn);
        btn->setText(file);
        connect(btn, &FileButton::SignalOpenFile, this, &OpenOldFileWidget::SignalOpenFile);
        ui->fileLayout->addWidget(btn);
    }
}

void OpenOldFileWidget::on_cancel_clicked()
{
    this->hide();
}
