#include "filedirutils.h"

#include <QDebug>
#include <QDir>
#include <QCryptographicHash>

QString FileDirUtils::GetCurrentPath()
{
    return QDir::currentPath();
}

QString FileDirUtils::GetAbsolutePath(const QString &file)
{
    QDir absolutePath;
    return absolutePath.absoluteFilePath(GetCurrentPath() + file);
}

QString FileDirUtils::GetMD5(const QString &str)
{
    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(str.toUtf8());
    return md5.result().toHex().constData();
}
