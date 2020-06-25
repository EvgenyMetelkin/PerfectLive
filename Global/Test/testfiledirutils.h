#ifndef TESTFILEDIRUTILS_H
#define TESTFILEDIRUTILS_H

#include <QtTest/QtTest>

class TestFileDirUtils : public QObject
{
    Q_OBJECT
public:
    TestFileDirUtils();

private slots:
    void getAbsolutePath();
};

#endif // TESTFILEDIRUTILS_H
