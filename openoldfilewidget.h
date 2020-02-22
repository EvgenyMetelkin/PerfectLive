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
    void signalOpenFile(QString &path);

public slots:
    void clickFileButton();

private:
    QString path;
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
    void signalOpenFile(QString &path);

public slots:
    void onShowOpenOldFileWidget(QDir &dir);

private slots:
    void on_cancel_clicked();

private:
    void findFile(QDir &dir);
    void appendListFilesToWidget();

private:
    Ui::OpenOldFileWidget *ui;
    QStringList listFiles;
    QList<FileButton*> listFileButton;
};

#endif // OPENOLDFILEWIDGET_H
