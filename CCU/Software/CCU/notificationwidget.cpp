#include "notificationWidget.h"
#include <QtWidgets>
#include <QApplication>

NotificationInfo NotificationWidget::getNotification()
{
    return notification;
}

void NotificationWidget::setNotification(NotificationInfo &value)
{
    notification = value;
}

NotificationWidget::NotificationWidget()
{

}

NotificationWidget::NotificationWidget(NotificationInfo nt, int xPos, int yPos)
{

    notification = nt;
    xPosition = xPos;
    yPosition = yPos;
    //paintDev = (&pDev);

    //notTitleLabel = new QPainter (&pDev);


}

void NotificationWidget::show(){

    //notTitleLabel->begin(paintDev);
    //notTitleLabel->setPen(QColor(220, 220, 220));
    //notTitleLabel->setFont(QFont("LCDMono", 50));
    //notTitleLabel->drawText(QRect(xPosition, yPosition ,120,100),QString::fromStdString(notification.getTitle()), Qt::AlignHCenter | Qt::AlignVCenter);
    //notTitleLabel->end();

}
