#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <notificationinfo.h>
#include <QtWidgets>
#include <QApplication>

class NotificationWidget
{
private:
    NotificationInfo notification;
    QPaintDevice paintDev;
    QPainter *notTitleLabel;
    int xPosition;
    int yPosition;

public:
    NotificationWidget();
    NotificationWidget(NotificationInfo nt, int xPos, int yPos, QPaintDevice pDev);
    NotificationInfo getNotification();
    void setNotification(NotificationInfo &value);

    void show();

};

#endif // NOTIFICATIONWIDGET_H
