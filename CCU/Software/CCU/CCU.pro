QT += widgets svg core gui serialport

greaterThan(QT_MAJOR_VERSION,4): QT += widgets

SOURCES += \
    main.cpp \
    cluster.cpp

DISTFILES += \
    img/outiline.svg

HEADERS += \
    cluster.h
