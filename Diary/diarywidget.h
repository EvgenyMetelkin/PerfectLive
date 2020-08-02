#ifndef DIARYWIDGET_H
#define DIARYWIDGET_H

#include <QMainWindow>
#include <QDir>
#include <QTimer>
#include <QTextStream>

#include "openoldfilewidget.h"
#include "modifyfile.h"
#include "rewritedialog.h"

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
    void HideDiary();

public slots:
    void OnOpenFile(QString &path);

private slots:
    void SaveFile();
    void NextWiseLine();

    void on_Save_clicked();
    void on_setBasePath_triggered();
    void on_changPath_triggered();
    void on_openOldFile_clicked();

    void on_Text_textChanged();

    void on_buttonBack_clicked();

private:
    int AddHistoryInDB();
    int GetBonus();
    void AddInfoBonus(QTextStream &out);

private:
    Ui::DiaryWidget *ui;
    OpenOldFileWidget m_openOldFileWidget;
    RewriteDialog m_rewriteDialog;
    QList<ModifyFile *> m_listModifyFiles;
    QDir m_dir;
    QTimer m_timerWiseLine;

};

#endif // DIARYWIDGET_H
