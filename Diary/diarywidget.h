#ifndef DIARYWIDGET_H
#define DIARYWIDGET_H

#include <QMainWindow>

#include "openoldfilewidget.h"
#include "modifyfile.h"

#include <QDir>

namespace Ui {
class DiaryWidget;
}

class DiaryWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit DiaryWidget(QWidget *parent = nullptr);
    ~DiaryWidget();

signals:
    void ShowOpenOldFileWidget(QDir &m_dir);

public slots:
    void OnOpenFile(QString &path);

private slots:
    void on_Save_clicked();
    void on_setBasePath_triggered();
    void on_changPath_triggered();

    void on_openOldFile_clicked();

private:
    Ui::DiaryWidget *ui;
    OpenOldFileWidget m_openOldFileWidget;
    QList<ModifyFile *> m_listModifyFiles;
    QDir m_dir;
};

#endif // DIARYWIDGET_H
