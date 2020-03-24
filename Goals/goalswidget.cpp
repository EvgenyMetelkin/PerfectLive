#include "goalswidget.h"
#include "ui_goalswidget.h"
#include "Global/filedirutils.h"

#include <QFile>
#include <QDebug>

GoalsWidget::GoalsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoalsWidget),
    m_goalsFileName("goals/goals.png"),
    m_subgoalCounter(0)
{
    ui->setupUi(this);

    ParseGoalFile();
}

GoalsWidget::~GoalsWidget()
{
    delete ui;
}

void GoalsWidget::ParseGoalFile()
{
    QFile goalsFile(FileDirUtils::GetAbsolutePath(m_goalsFileName));
    if(!goalsFile.exists()) {
        qDebug() << "GoalsWidget::ParseGoalFile: Error, m_goalsFileName not exists";
        return;
    }
    if (!goalsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "GoalsWidget::ParseGoalFile: Error, don't open";
        return;
    }

    QTextStream in(&goalsFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        ParseGoalsLine(line);
    }
}

void GoalsWidget::ParseGoalsLine(const QString &goalsLine)
{
    if(goalsLine.startsWith("*")) {
        ui->pteGoals->appendPlainText(QString("    %1").arg(++m_subgoalCounter) + ") " + goalsLine);
    } else {
        m_subgoalCounter = 0;
        ui->pteGoals->appendPlainText(goalsLine);
    }
}


















