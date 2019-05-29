#-------------------------------------------------
#
# Project created by QtCreator 2019-05-28T14:35:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 1.0
QMAKE_TARGET_PRODUCT = pdfUnify
QMAKE_TARGET_DESCRIPTION = Program to combine images and pdf
QMAKE_TARGET_COPYRIGHT = Korshunov Ruslan (Sungurov Ruslan)

RC_ICONS = images\icon.ico

TARGET = pdfUnify
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
        pdfUnify.cpp

HEADERS += \
        mainwindow.h \
        pdfUnify.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -lFreeType
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -lFreeType

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/libFreeType.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/libFreeType.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/FreeType.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/FreeType.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -lLibAesgm
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -lLibAesgm

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/libLibAesgm.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/libLibAesgm.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/LibAesgm.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/LibAesgm.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -lLibJpeg
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -lLibJpeg

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/libLibJpeg.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/libLibJpeg.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/LibJpeg.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/LibJpeg.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -lLibPng
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -lLibPng

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/libLibPng.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/libLibPng.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/LibPng.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/LibPng.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -lLibTiff
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -lLibTiff

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/libLibTiff.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/libLibTiff.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/LibTiff.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/LibTiff.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -lZlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -lZlib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/libZlib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/libZlib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/Zlib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/Zlib.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/release/ -lPDFWriter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/debug/ -lPDFWriter

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/libPDFWriter.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/libPDFWriter.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/release/PDFWriter.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/debug/PDFWriter.lib
