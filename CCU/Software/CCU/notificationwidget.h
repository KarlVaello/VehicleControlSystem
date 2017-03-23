#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <notificationInfo.h>
#include <QtWidgets>
#include <QApplication>

class NotificationWidget
{
private:
    NotificationInfo *notificationInfo;
    QPaintDevice *painterDevice;
    QPainter *notificationTitleLabel;
    QPainter *notificationIcon;
    int xPosition;
    int yPosition;

public:
    NotificationWidget();
    NotificationWidget(NotificationInfo *nt, int xPos, int yPos,QPaintDevice *pntDvc);
    NotificationInfo getNotification();

    void show();

};

#endif // NOTIFICATIONWIDGET_H
