#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Password/passwordwidget.h"
#include "Diary/diarywidget.h"
#include "Goals/goalswidget.h"
#include "Earned/chartofearned.h"

#define ORGANIZATION_NAME "OOO EvgMet"
#define ORGANIZATION_DOMAIN "www.evg_met.ru"
#define APPLICATION_NAME "PerfectLive"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ConfirmedPassword();

private slots:
    void on_bDiary_clicked();

    void on_bGoals_clicked();

    void on_bChangeWiseLine_clicked();

private:
    void ShowMainWindow();
    void ViewChartOfEarned();

private:
    Ui::MainWindow *ui;
    PasswordWidget m_passwordWidget;
    DiaryWidget m_diaryWidget;
    GoalsWidget m_goalsWidget;
    ChartOfEarned m_chartOfEarned;
};
#endif // MAINWINDOW_H
