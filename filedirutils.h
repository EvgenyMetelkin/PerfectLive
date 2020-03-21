#ifndef FILEDIRUTILS_H
#define FILEDIRUTILS_H

#include <QString>

class FileDirUtils
{
public:
    static QString GetCurrentPath();
    static QString GetAbsolutePath(const QString &file);
};

#endif // FILEDIRUTILS_H
