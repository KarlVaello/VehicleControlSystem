QT += widgets svg core gui serialport

greaterThan(QT_MAJOR_VERSION,4): QT += widgets

SOURCES += \
    main.cpp \
    cluster.cpp \
    notificationinfo.cpp \
    notificationwidget.cpp

DISTFILES += \
    img/outiline.svg \
    img/speedPointer.svg

HEADERS += \
    cluster.h \
    notificationinfo.h \
    notificationwidget.h

RESOURCES += \
    resources.qrc
