#ifndef FILEDIRUTILS_H
#define FILEDIRUTILS_H

#include <QString>

#define DATABASE_HOSTNAME   "PerfectLive"
#define DATABASE_NAME       "PerfectLive.db"

class FileDirUtils
{
public:
    static QString getCurrentPath();
    static QString getAbsolutePath(const QString &file);
    static QString getMD5(const QString &str);
};

#endif // FILEDIRUTILS_H
