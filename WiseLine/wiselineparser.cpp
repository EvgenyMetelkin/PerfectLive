#include "wiselineparser.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QTextCodec>

#define MAX_CHAR_IN_LINE 141

QString WiseLineParser::GetWiseLine()
{
    QFile file(":/wiseline/wiselines.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    in.setCodec(QTextCodec::codecForName("UTF-8"));

    int countLine = in.readLine().toInt();
    int randomLine = randomBetween(1, countLine);

    QString wiseLine = "";

    for (int i = 0; i < randomLine && !in.atEnd(); ++i) {
        wiseLine = in.readLine();
    }
    file.close();

    lineBreak(wiseLine);

    return wiseLine;
}

int WiseLineParser::randomBetween(int low, int high)
{
    qsrand((unsigned int)QDateTime::currentMSecsSinceEpoch()); // Установка базового числа для отсчёта рандома в qrand
    return (qrand() % ((high + 1) - low) + low);
}

void WiseLineParser::lineBreak(QString &wiseLine)
{
    if(wiseLine.size() < MAX_CHAR_IN_LINE)
        return;

    for(int j = 1; wiseLine.size() > MAX_CHAR_IN_LINE * j; ++j) {
        for(int i = MAX_CHAR_IN_LINE * j; i < wiseLine.size() && i > 0; --i) {
            if(wiseLine[i] == " ") {
                wiseLine[i] = '\n';
                break;
            }
        }
    }
}

