#ifndef DIARYWIDGET_H
#define DIARYWIDGET_H

#include <QMainWindow>
#include <QSettings>

#include "openoldfilewidget.h"
#include "modifyfile.h"

#include <QDir>

#define ORGANIZATION_NAME "OOO EvgMet"
#define ORGANIZATION_DOMAIN "www.evg_met.ru"
#define APPLICATION_NAME "PerfectLive"

#define SETTINGS_DIR "settings/dir"

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
    void showOpenOldFileWidget(QDir &dir);

public slots:
    void onOpenFile(QString &path);

private slots:
    void on_Save_clicked();
    void on_setBasePath_triggered();
    void on_changPath_triggered();

    void on_openOldFile_clicked();

private:
    Ui::DiaryWidget *ui;
    OpenOldFileWidget openOldFileWidget;
    QList<ModifyFile *> listModifyFiles;
    QDir dir;
};

#endif // DIARYWIDGET_H
