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
    qDebug() << Q_FUNC_INFO << "absolutePath.absoluteFilePath(file) " << absolutePath.absoluteFilePath(file);
    return absolutePath.absoluteFilePath(GetCurrentPath() + file);
}

