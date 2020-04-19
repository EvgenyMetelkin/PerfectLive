#include "filedirutils.h"

#include <QDebug>
#include <QDir>

QString FileDirUtils::GetCurrentPath()
{
    return QDir::currentPath();
}

QString FileDirUtils::GetAbsolutePath(const QString &file)
{
    QDir absolutePath;
    return absolutePath.absoluteFilePath(GetCurrentPath() + file);
}

