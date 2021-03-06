QT += core gui charts sql testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Census/censustablemodel.cpp \
    Census/censuswidget.cpp \
    Census/dbcensus.cpp \
    Diary/Test/testhistorycreationdiary.cpp \
    Diary/dbhistorydiary.cpp \
    Diary/diarywidget.cpp \
    Diary/historycreationdiary.cpp \
    Diary/rewritedialog.cpp \
    Global/Test/testfiledirutils.cpp \
    Global/filedirutils.cpp \
    Global/settings.cpp \
    Goals/goalswidget.cpp \
    Income/dbincome.cpp \
    Income/earnbyhour.cpp \
    Income/incomeview.cpp \
    Style/mainstyle.cpp \
    main.cpp \
    mainwindow.cpp \
    Diary/modifyfile.cpp \
    Diary/openoldfilewidget.cpp \
    Password/passwordwidget.cpp \
    WiseLine/wiselineparser.cpp

HEADERS += \
    Census/censustablemodel.h \
    Census/censuswidget.h \
    Census/dbcensus.h \
    Diary/Test/testhistorycreationdiary.h \
    Diary/dbhistorydiary.h \
    Diary/diarywidget.h \
    Diary/historycreationdiary.h \
    Diary/rewritedialog.h \
    Global/Test/testfiledirutils.h \
    Global/filedirutils.h \
    Global/settings.h \
    Goals/goalswidget.h \
    Income/dbincome.h \
    Income/earnbyhour.h \
    Income/incomeview.h \
    Style/mainstyle.h \
    mainwindow.h \
    Diary/modifyfile.h \
    Diary/openoldfilewidget.h \
    Password/passwordwidget.h \
    WiseLine/wiselineparser.h

FORMS += \
    Census/censuswidget.ui \
    Diary/diarywidget.ui \
    Diary/rewritedialog.ui \
    Goals/goalswidget.ui \
    mainwindow.ui \
    Diary/modifyfile.ui \
    Diary/openoldfilewidget.ui \
    Password/passwordwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource/resource.qrc

# ! иконка работает только в windows
win32: RC_ICONS = $$PWD/Resource/icon.ico


