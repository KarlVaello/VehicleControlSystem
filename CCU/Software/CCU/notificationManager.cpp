#include "notificationManager.h"
#include <notificationInfo.h>

QList<NotificationInfo *> NotificationManager::getNotificationList()
{
    return notificationList;
}

void NotificationManager::setNotificationList(QList<NotificationInfo *> value)
{
    notificationList = value;
}

NotificationManager::NotificationManager()
{

}


void NotificationManager::apendNotification(NotificationInfo *ntI){

    notificationList.append(ntI);
}

