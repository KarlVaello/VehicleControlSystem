#ifndef NOTIFICATIONWIDGETMANAGER_H
#define NOTIFICATIONWIDGETMANAGER_H

#include <notificationWidget.h>

class NotificationWidgetManager
{

private:
    QList<NotificationWidget*> notificationWidgetList;

public:
    NotificationWidgetManager();

    void apendNotificationWidget(NotificationWidget *ntWidget);

    QList<NotificationWidget *> getNotificationWidgetList();
    void setNotificationWidgetList(QList<NotificationWidget *> &value);
};

#endif // NOTIFICATIONWIDGETMANAGER_H
