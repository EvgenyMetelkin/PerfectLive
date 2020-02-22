#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "passwordwidget.h"
#include "diarywidget.h"

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
    void confirmedBasePassword();
    void confirmedMainPassword();

private slots:
    void on_bDiary_clicked();

private:
    void showMainWindow();

private:
    Ui::MainWindow *ui;
    PasswordWidget passwordWidget;
    bool mainMod;
    DiaryWidget diaryWidget;
};
#endif // MAINWINDOW_H
