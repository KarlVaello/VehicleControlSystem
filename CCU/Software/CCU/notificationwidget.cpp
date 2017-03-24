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
    notificationIconPainter = new QPainter(painterDevice);
    notificationIconPainter->end();
    notificationIconRenderer = new QSvgRenderer(QString(":/img/errorIcon.svg"));

    notificationInfo = nt;
    xPosition = xPos;
    yPosition = yPos;



}

void NotificationWidget::show(){

    notificationIconPainter->begin(painterDevice);
    notificationIconRenderer->render(notificationIconPainter,QRect(xPosition, yPosition,30,30) );
    notificationIconPainter->end();

    notificationTitleLabel->begin(painterDevice);
    notificationTitleLabel->setPen(QColor(220, 220, 220));
    notificationTitleLabel->setFont(QFont("Arial", 14));
    notificationTitleLabel->drawText(QRect(xPosition + 35, yPosition + 9 ,120,100),QString::fromStdString(notificationInfo->getTitle()));
    notificationTitleLabel->end();

}
