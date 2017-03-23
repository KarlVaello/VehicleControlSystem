QT += widgets svg core gui serialport

greaterThan(QT_MAJOR_VERSION,4): QT += widgets

SOURCES += \
    main.cpp \
    cluster.cpp \
    notificationInfo.cpp \
    notificationManager.cpp \
    notificationWidget.cpp \
    notificationWidgetManager.cpp

DISTFILES += \
    img/outiline.svg \
    img/speedPointer.svg

HEADERS += \
    cluster.h \
    notificationInfo.h \
    notificationManager.h \
    notificationWidget.h \
    notificationWidgetManager.h

RESOURCES += \
    resources.qrc
