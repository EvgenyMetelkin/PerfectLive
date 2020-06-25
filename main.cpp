#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>

#include "Global/Test/testfiledirutils.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION_NAME);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QTest::qExec(new TestFileDirUtils, argc, argv);

    QApplication a(argc, argv);
    MainWindow w;
    return a.exec();
}
