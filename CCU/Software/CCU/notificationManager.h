#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QList>
#include <notificationInfo.h>

class NotificationManager
{
private:
    QList<NotificationInfo*> notificationList;

public:
    NotificationManager();
    void apendNotification(NotificationInfo *ntI);

    QList<NotificationInfo*> getNotificationList();
    void setNotificationList(QList<NotificationInfo *> value);
};


#endif // NOTIFICATIONMANAGER_H
