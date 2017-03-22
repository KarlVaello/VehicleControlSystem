#include "notificationinfo.h"
#include <string>

NotificationInfo::NotificationInfo(){}

NotificationInfo::NotificationInfo(int ty)
{
    type = ty;
}


NotificationInfo::NotificationInfo(int ty, std::string tl)
{
    type = ty;
    title = tl;
}
std::string NotificationInfo::getTitle(){
    return title;
}
