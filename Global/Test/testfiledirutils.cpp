#include "testfiledirutils.h"
#include "../filedirutils.h"

TestFileDirUtils::TestFileDirUtils()
{

}

void TestFileDirUtils::getAbsolutePath()
{
    QCOMPARE(FileDirUtils::getAbsolutePath(""), QString("D:/MyProg/QtCreator/build-PerfectLive-Desktop_Qt_5_11_3_MinGW_32bit-Debug/"));
    QCOMPARE(FileDirUtils::getAbsolutePath("fileName"), QString("D:/MyProg/QtCreator/build-PerfectLive-Desktop_Qt_5_11_3_MinGW_32bit-Debug/fileName"));
    QCOMPARE(FileDirUtils::getAbsolutePath("*@h123lhn1o-dfk"), QString("D:/MyProg/QtCreator/build-PerfectLive-Desktop_Qt_5_11_3_MinGW_32bit-Debug/*@h123lhn1o-dfk"));
}
