#ifndef GOALSWIDGET_H
#define GOALSWIDGET_H

#include <QWidget>

namespace Ui {
class GoalsWidget;
}

class GoalsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GoalsWidget(QWidget *parent = nullptr);
    ~GoalsWidget();

private:
    void ParseGoalFile();
    void ParseGoalsLine(const QString &goalsLine);

private:
    Ui::GoalsWidget *ui;
    QString m_goalsFileName;
    int m_subgoalCounter;

};

#endif // GOALSWIDGET_H
