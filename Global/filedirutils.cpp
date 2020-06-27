#include "filedirutils.h"

#include <QDebug>
#include <QDir>
#include <QCryptographicHash>

QString FileDirUtils::getCurrentPath()
{
    return QDir::currentPath() + /*QDir::separator()*/ '/';
}

QString FileDirUtils::getAbsolutePath(const QString &file)
{
    QDir absolutePath;
    return absolutePath.absoluteFilePath(getCurrentPath() + file);
}

QString FileDirUtils::getMD5(const QString &str)
{
    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(str.toUtf8());
    return md5.result().toHex().constData();
}
