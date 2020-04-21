#ifndef FILEDIRUTILS_H
#define FILEDIRUTILS_H

#include <QString>

class FileDirUtils
{
public:
    static QString GetCurrentPath();
    static QString GetAbsolutePath(const QString &file);
    static QString GetMD5(const QString &str);
};

#endif // FILEDIRUTILS_H
