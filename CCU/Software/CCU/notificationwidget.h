#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <notificationInfo.h>
#include <QtWidgets>
#include <QApplication>
#include <QtSvg/QtSvg>
#include <QtSvg/QSvgRenderer>

class NotificationWidget
{
private:
    NotificationInfo *notificationInfo;
    QPaintDevice *painterDevice;
    QPainter *notificationTitleLabel;
    QPainter *notificationIconPainter;

    QSvgRenderer *notificationIconRenderer;

    int xPosition;
    int yPosition;

public:
    NotificationWidget();
    NotificationWidget(NotificationInfo *nt, int xPos, int yPos,QPaintDevice *pntDvc);
    NotificationInfo getNotification();

    void show();

};

#endif // NOTIFICATIONWIDGET_H
