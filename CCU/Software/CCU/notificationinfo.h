#ifndef NOTIFICATIONINFO_H
#define NOTIFICATIONINFO_H

#include <string>
class NotificationInfo
{
private:
    int type;
    std::string title;

public:
    NotificationInfo();
    NotificationInfo(int ty);
    NotificationInfo(int ty, std::string tl);
    std::string getTitle();
};

#endif // NOTIFICATIONINFO_H
