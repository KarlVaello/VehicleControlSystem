QT += widgets svg core gui serialport multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION,4): QT += widgets

SOURCES += \
    main.cpp \
    cluster.cpp \
    notificationInfo.cpp \
    notificationManager.cpp \
    notificationWidget.cpp \
    notificationWidgetManager.cpp \
    cameraStream.cpp \
    unitCommunication.cpp \
    infotainment.cpp \
    cameraCaptureBuffer.cpp

DISTFILES += \
    img/outiline.svg \
    img/speedPointer.svg

HEADERS += \
    cluster.h \
    notificationInfo.h \
    notificationManager.h \
    notificationWidget.h \
    notificationWidgetManager.h \
    cameraStream.h \
    unitCommunication.h \
    infotainment.h \
    cameraCaptureBuffer.h

RESOURCES += \
    resources.qrc
