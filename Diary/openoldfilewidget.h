#ifndef OPENOLDFILEWIDGET_H
#define OPENOLDFILEWIDGET_H

#include <QWidget>
#include <QDir>
#include <QPushButton>

class FileButton : public QPushButton
{
    Q_OBJECT

public:
     FileButton(QString &path, QWidget *parent = nullptr);

signals:
    void SignalOpenFile(QString &path);

public slots:
    void ClickFileButton();

private:
    QString m_path;
};


namespace Ui {
class OpenOldFileWidget;
}

class OpenOldFileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OpenOldFileWidget(QWidget *parent = nullptr);
    ~OpenOldFileWidget();

signals:
    void SignalOpenFile(QString &path);

public slots:
    void OnShowOpenOldFileWidget(QDir &dir);

private slots:
    void on_cancel_clicked();

private:
    void FindFile(QDir &dir);
    void AppendListFilesToWidget();

private:
    Ui::OpenOldFileWidget *ui;
    QStringList m_listFiles;
    QList<FileButton*> m_listFileButton;
};

#endif // OPENOLDFILEWIDGET_H
