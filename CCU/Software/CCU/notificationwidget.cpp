#include "notificationWidget.h"
#include <QtWidgets>
#include <QApplication>

NotificationWidget::NotificationWidget()
{

}

NotificationWidget::NotificationWidget(NotificationInfo *nt, int xPos, int yPos, QPaintDevice *pntDvc)
{

    painterDevice =  (pntDvc);
    notificationTitleLabel = new QPainter(painterDevice);
    notificationTitleLabel->end();
    notificationIcon = new QPainter(painterDevice);
    notificationIcon->end();
    notificationInfo = nt;
    xPosition = xPos;
    yPosition = yPos;

    //notTitleLabel = new QPainter (&pDev);


}

void NotificationWidget::show(){

    notificationTitleLabel->begin(painterDevice);
    notificationTitleLabel->setPen(QColor(220, 220, 220));
    notificationTitleLabel->setFont(QFont("Arial", 8));
    notificationTitleLabel->drawText(QRect(xPosition, yPosition ,120,100),QString::fromStdString(notificationInfo->getTitle()));
    notificationTitleLabel->end();

}
