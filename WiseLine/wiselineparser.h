#ifndef WISELINEPARSER_H
#define WISELINEPARSER_H

#include <QString>

class WiseLineParser
{
public:
    static QString GetWiseLine();
private:
    static int RandomBetween(int low, int high);
};

#endif // WISELINEPARSER_H
