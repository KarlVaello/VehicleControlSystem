#include "notificationWidget.h"
#include <QtWidgets>
#include <QApplication>

NotificationWidget::NotificationWidget()
{

}

NotificationWidget::NotificationWidget(NotificationInfo *nt, int xPos, int yPos, QPaintDevice *pntDvc)
{
    notificationInfo = nt;
    xPosition = xPos;
    yPosition = yPos;
    painterDevice =  (pntDvc);
    type = nt->getType();
    qDebug()<< "notification type: " << type ;


    if(type == 0){
        notificationTitleLabel = new QPainter(painterDevice);
        notificationTitleLabel->end();
    }
    notificationIconPainter = new QPainter(painterDevice);
    notificationIconPainter->end();
    notificationIconRenderer = new QSvgRenderer(QString(":/img/errorIcon.svg"));





}

void NotificationWidget::show(){

    notificationIconPainter->begin(painterDevice);
    notificationIconRenderer->render(notificationIconPainter,QRect(xPosition, yPosition,30,30) );
    notificationIconPainter->end();

    if(type == 0){
        notificationTitleLabel->begin(painterDevice);
        notificationTitleLabel->setPen(QColor(220, 220, 220));
        notificationTitleLabel->setFont(QFont("Arial", 14));
        notificationTitleLabel->drawText(QRect(xPosition + 35, yPosition + 9 ,120,100),QString::fromStdString(notificationInfo->getTitle()));
        notificationTitleLabel->end();
    }

}
