#-------------------------------------------------
#
# Project created by QtCreator 2018-09-26T22:19:18
#
#-------------------------------------------------

QT       += core gui widgets

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
    sidebar.cpp

HEADERS += \
        mainwindow.h \
    scenezoom.h \
    sidebar.h

FORMS += \
        mainwindow.ui

RESOURCES += resource.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /usr/local/include/gdcm-2.8/
LIBS += -lgdcmcharls -L/usr/local/lib/gdcm-2.8/ \
        -lgdcmCommon -L/usr/local/lib/gdcm-2.8/ \
        -lgdcmDICT -L/usr/local/lib/gdcm-2.8/ \
        -lgdcmDSED -L/usr/local/lib/gdcm-2.8/ \
        -lgdcmexpat -L/usr/local/lib/gdcm-2.8/ \
        -lgdcmIOD -L/usr/local/lib/gdcm-2.8/ \
        -lgdcmjpeg12 -L/usr/local/lib/gdcm-2.8/ \
        -lgdcmjpeg16 -L/usr/local/lib/gdcm-2.8/ \
        -lgdcmjpeg8 -L/usr/local/lib/gdcm-2.8/ \
        -lgdcmMEXD -L/usr/local/lib/gdcm-2.8/ \
        -lgdcmMSFF -L/usr/local/lib/gdcm-2.8/ \
        -lgdcmopenjp2 -L/usr/local/lib/gdcm-2.8/ \
        -lgdcmuuid -L/usr/local/lib/gdcm-2.8/ \
        -lgdcmzlib -L/usr/local/lib/gdcm-2.8/ \
        -lsocketxx -L/usr/local/lib/gdcm-2.8/ \
         -lgdcmjpeg8 -L/usr/local/lib/gdcm-2.8/
