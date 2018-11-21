#-------------------------------------------------
#
# Project created by QtCreator 2018-09-26T22:19:18
#
#-------------------------------------------------

QT       += core gui widgets sql network

TARGET = newDicomClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    scenezoom.cpp \
    sidebar.cpp \
    converters.cpp \
    viewerform.cpp \
    tagshelpers.cpp \
    accessibilityform.cpp \
    dbform.cpp \
    logger.cpp \
    serializehelper.cpp \
    server.cpp \
    client.cpp \
    task.cpp \
    telemedobject.cpp

HEADERS += \
        mainwindow.h \
    scenezoom.h \
    sidebar.h \
    converters.h \
    viewerform.h \
    tagshelpers.h \
    accessibilityform.h \
    dbform.h \
    logger.h \
    serializehelper.h \
    server.h \
    client.h \
    task.h \
    telemedobject.h

FORMS += \
        mainwindow.ui \
        viewerform.ui \
    accessibilityform.ui \
    dbform.ui

RESOURCES += resource.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += ../include/gdcm-2.8/
LIBS += -lgdcmcharls -L../lib/gdcm-2.8/ \
        -lgdcmCommon -L../lib/gdcm-2.8/ \
        -lgdcmDICT -L../lib/gdcm-2.8/ \
        -lgdcmDSED -L../lib/gdcm-2.8/ \
        -lgdcmexpat -L../lib/gdcm-2.8/ \
        -lgdcmIOD -L../lib/gdcm-2.8/ \
        -lgdcmjpeg12 -L../lib/gdcm-2.8/ \
        -lgdcmjpeg16 -L../lib/gdcm-2.8/ \
        -lgdcmjpeg8 -L../lib/gdcm-2.8/ \
        -lgdcmMEXD -L../lib/gdcm-2.8/ \
        -lgdcmMSFF -L../lib/gdcm-2.8/ \
        -lgdcmopenjp2 -L../lib/gdcm-2.8/ \
        -lgdcmuuid -L../lib/gdcm-2.8/ \
        -lgdcmzlib -L../lib/gdcm-2.8/ \
        -lsocketxx -L../lib/gdcm-2.8/ \
         -lgdcmjpeg8 -L../lib/gdcm-2.8/
