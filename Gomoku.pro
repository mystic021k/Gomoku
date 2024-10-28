QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gomokuai.cpp \
    main.cpp \
    gomoku.cpp \
    qgomokuview.cpp \
    qgamehelpdlg.cpp \
    gomokuengine.cpp
    gomokuai.cpp

HEADERS += \
    gomoku.h \
    gomokuai.h \
    qgomokuview.h \
    qgamehelpdlg.h \
    gomokuengine.h
    gomokuai.h

FORMS += \
    gomoku.ui \
    gamehelp.ui

RESOURCES += \
    gomoku.qrc

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS += \
    Gomoku_zh_CN.ts
