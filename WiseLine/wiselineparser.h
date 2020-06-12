#ifndef WISELINEPARSER_H
#define WISELINEPARSER_H

#include <QString>

class WiseLineParser
{
public:
    static QString GetWiseLine();
private:
    static int randomBetween(int low, int high);
    static void lineBreak(QString &wiseLine);
};

#endif // WISELINEPARSER_H
