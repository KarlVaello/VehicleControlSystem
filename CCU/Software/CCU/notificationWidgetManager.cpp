#include "notificationWidgetManager.h"

QList<NotificationWidget *> NotificationWidgetManager::getNotificationWidgetList()
{
    return notificationWidgetList;
}

void NotificationWidgetManager::setNotificationWidgetList( QList<NotificationWidget *> &value)
{
    notificationWidgetList = value;
}

NotificationWidgetManager::NotificationWidgetManager()
{

}

void NotificationWidgetManager::apendNotificationWidget(NotificationWidget *ntWidget)
{

    notificationWidgetList.append(ntWidget);


}
