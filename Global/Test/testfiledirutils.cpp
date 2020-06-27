#include "testfiledirutils.h"
#include "../filedirutils.h"

TestFileDirUtils::TestFileDirUtils()
{

}

void TestFileDirUtils::getCurrentPath()
{
    QCOMPARE(FileDirUtils::getCurrentPath(), QString("D:/MyProg/QtCreator/build-PerfectLive-Desktop_Qt_5_11_3_MinGW_32bit-Debug/"));

}

void TestFileDirUtils::getAbsolutePath()
{
    QCOMPARE(FileDirUtils::getAbsolutePath(""), QString("D:/MyProg/QtCreator/build-PerfectLive-Desktop_Qt_5_11_3_MinGW_32bit-Debug/"));
    QCOMPARE(FileDirUtils::getAbsolutePath("fileName"), QString("D:/MyProg/QtCreator/build-PerfectLive-Desktop_Qt_5_11_3_MinGW_32bit-Debug/fileName"));
    QCOMPARE(FileDirUtils::getAbsolutePath("*@h123lhn1o-dfk"), QString("D:/MyProg/QtCreator/build-PerfectLive-Desktop_Qt_5_11_3_MinGW_32bit-Debug/*@h123lhn1o-dfk"));
}

void TestFileDirUtils::getMD5()
{
    QCOMPARE(FileDirUtils::getMD5(""), QString("d41d8cd98f00b204e9800998ecf8427e"));
    QCOMPARE(FileDirUtils::getMD5("4444"), QString("dbc4d84bfcfe2284ba11beffb853a8c4"));
}
