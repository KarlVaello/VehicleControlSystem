#include "cluster.h"
#include <QtWidgets>
#include <QApplication>
#include <QtSvg/QtSvg>
#include <QtSvg/QSvgRenderer>
#include <QDebug>
#include <QPixmap>
#include <string>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <iostream>
#include <notificationInfo.h>
#include <notificationManager.h>
#include <notificationWidget.h>
#include <notificationWidgetManager.h>
#include <QDateTime>
#include <unitCommunication.h>
#include <infotainment.h>

Cluster::Cluster(QWidget *parent , UnitCommunication *ccu_COM, Infotainment *infota
                 )
    : QWidget(parent)
{

    infotaiment = infota;
    centralControlUnit_COM = ccu_COM;
    time = new QTime();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1);
    setWindowTitle(tr("Analog Clock"));


    resize(1280, 480);

    ntManager = new NotificationManager();

    ntWidgetManager = new NotificationWidgetManager();
    qDebug() << "Types:" << QString::number(ntManager->getNotificationList().count()) << "\n";

    /*if(!serialConnection){

        NotificationInfo *n01 = new NotificationInfo(1,"Serial Error");
        ntManager->apendNotification(n01);

        NotificationWidget *a = new NotificationWidget(ntManager->getNotificationList().at(0),250,200,this);
        ntWidgetManager->apendNotificationWidget(a);

        qDebug() << "Types:" << QString::number(ntManager->getNotificationList().count()) << "\n";
    }*/

    outlineRenderer = new QSvgRenderer(QString(":/img/outline.svg"));
    speedPointerRenderer = new QSvgRenderer(QString(":/img/speedPointer.svg"));
    notificationBannerRenderer = new QSvgRenderer(QString(":/img/notificationBanner.svg"));
}

void Cluster::paintEvent(QPaintEvent *)
{
    if(!isInitClusterAnim_outline && !isInitClusterAnim_speedPointer){
        backGroundRect->begin(this);
        backGroundRect->fillRect(QRect(0,0,1280,480),QColor(30,30,30,255));
        backGroundRect->end();

        painterOutline->begin(this);
        outlineOpacity = outlineOpacity + 0.008f;
        painterOutline->setOpacity(outlineOpacity);
        outlineRenderer->render(painterOutline);
        painterOutline->end();

        if(outlineOpacity >= 1.0f){
            isInitClusterAnim_outline = true;
            qDebug() << "outline_init_end";
        }

    }else if(isInitClusterAnim_outline && !isInitClusterAnim_speedPointer){

        backGroundRect->begin(this);
        backGroundRect->fillRect(QRect(0,0,1280,480),QColor(30,30,30,255));
        backGroundRect->end();

        painterOutline->begin(this);
        outlineRenderer->render(painterOutline);
        painterOutline->end();

        currentSpeed = currentSpeed - 2;
        currentLabelSpeed = currentSpeed;
        lastSpeed = currentSpeed;

        postOpacity = postOpacity + 0.008f;

        painterSpeedPointer->begin(this);
        painterSpeedPointer->setOpacity(postOpacity);
        painterSpeedPointer->translate(1280/2, 480/2);
        painterSpeedPointer->rotate((lastSpeed + ((currentSpeed - lastSpeed)/2)) * 0.845f);
        speedPointerRenderer->render(painterSpeedPointer);
        painterSpeedPointer->end();

        speedLabel->begin(this);
        speedLabel->setOpacity(postOpacity);
        speedLabel->setPen(QColor(220, 220, 220));
        speedLabel->setFont(QFont("LCDMono", 55));
        speedLabel->drawText(QRect(580, 180 ,120,100),QString::number(currentLabelSpeed), Qt::AlignHCenter | Qt::AlignVCenter);
        speedLabel->end();

        painter_timeLabel->begin(this);
        painter_timeLabel->setOpacity(postOpacity);
        painter_timeLabel->setPen(QColor(220, 220, 220));
        painter_timeLabel->setFont(QFont("LCDMono", 20));
        painter_timeLabel->drawText(QRect(580, 30 ,120,30),time->currentTime().toString(), Qt::AlignHCenter | Qt::AlignVCenter);
        painter_timeLabel->end();

        if(currentSpeed <= 0){
            isInitClusterAnim_speedPointer = true;
            currentSpeed = 0;
            qDebug() << "speedPointer_init_end";
        }

    }else{
        //connect(centralControlUnit_COM->getDataIn_port(), &QSerialPort::readyRead, this, &Cluster::readData);
        //connect(centralControlUnit_COM->getDataIn_port(), &QSerialPort::readyRead, this, &Cluster::readData);
        //centralControlUnit_COM->readData();
        //connect(centralControlUnit_COM->getDataIn_port(), &QSerialPort::readyRead, centralControlUnit_COM, &UnitCommunication::readData);
        centralControlUnit_COM->readData();

        painterOutline->begin(this);
        outlineRenderer->render(painterOutline);
        painterOutline->end();

        painterSpeedPointer->begin(this);
        painterSpeedPointer->translate(1280/2, 480/2);
        //painterSpeedPointer->rotate((lastSpeed + ((currentSpeed - lastSpeed)/2)) * 0.845f);
        painterSpeedPointer->rotate(infotaiment->getSpeed() * 0.845f);
        speedPointerRenderer->render(painterSpeedPointer);
        painterSpeedPointer->end();

        rS++;
        if(rS > 6){
            currentLabelSpeed = (int)currentSpeed;
            rS = 0;
        }

        painter_timeLabel->begin(this);
        painter_timeLabel->setOpacity(painter_timeLabel->opacity() + 0.01f);
        painter_timeLabel->setPen(QColor(220, 220, 220));
        painter_timeLabel->setFont(QFont("LCDMono", 20));
        painter_timeLabel->drawText(QRect(580, 30 ,120,30),time->currentTime().toString(), Qt::AlignHCenter | Qt::AlignVCenter);
        painter_timeLabel->end();

        speedLabel->begin(this);
        speedLabel->setPen(QColor(220, 220, 220));
        speedLabel->setFont(QFont("LCDMono", 55));
        speedLabel->drawText(QRect(580, 180 ,120,100),QString::number(infotaiment->getSpeed()), Qt::AlignHCenter | Qt::AlignVCenter);
        speedLabel->end();

        //ntWidgetManager->getNotificationWidgetList().at(0)->show();
    }
}
