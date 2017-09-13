#include "cluster.h"
#include <QtWidgets>
#include <QApplication>
#include <QtSvg/QtSvg>
#include <QtSvg/QSvgRenderer>
#include <QDebug>
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
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(1);
    setWindowTitle(tr("VCS"));

    resize(1280, 480);

    //ntManager = new NotificationManager();

    //ntWidgetManager = new NotificationWidgetManager();
    //qDebug() << "Types:" << QString::number(ntManager->getNotificationList().count()) << "\n";

    /*if(!serialConnection){

        NotificationInfo *n01 = new NotificationInfo(1,"Serial Error");
        ntManager->apendNotification(n01);

        NotificationWidget *a = new NotificationWidget(ntManager->getNotificationList().at(0),250,200,this);
        ntWidgetManager->apendNotificationWidget(a);

        qDebug() << "Types:" << QString::number(ntManager->getNotificationList().count()) << "\n";
    }*/

    outlineRenderer = new QSvgRenderer(QString(":/img/outline.svg"));
    speedPointerRenderer = new QSvgRenderer(QString(":/img/speedPointer.svg"));




}

void Cluster::paintEvent(QPaintEvent *)
{

    if(!isInitClusterAnim_outline && !isInitClusterAnim_speedPointer){


        QPainter *backGroundRect = new QPainter(this);
        backGroundRect->fillRect(QRect(0,0,1280,480),QColor(30,30,30,255));
        backGroundRect->end();

        QPainter *painterOutline = new QPainter(this);
        outlineOpacity = outlineOpacity + 0.008f;
        painterOutline->setOpacity(outlineOpacity);
        outlineRenderer->render(painterOutline);
        painterOutline->end();

        if(outlineOpacity >= 1.0f){
            isInitClusterAnim_outline = true;
            //qDebug() << "outline_init_end";
        }

    } else if(isInitClusterAnim_outline && !isInitClusterAnim_speedPointer){

        QPainter *backGroundRect = new QPainter(this);
        backGroundRect->fillRect(QRect(0,0,1280,480),QColor(30,30,30,255));
        backGroundRect->end();

        QPainter *painterOutline = new QPainter(this);
        outlineRenderer->render(painterOutline);
        painterOutline->end();

        currentSpeed = currentSpeed - 2;
        currentLabelSpeed = currentSpeed;
        lastSpeed = currentSpeed;

        postOpacity = postOpacity + 0.008f;

        QPainter *painterSpeedPointer = new QPainter(this);
        painterSpeedPointer->setOpacity(postOpacity);
        painterSpeedPointer->translate(1280/2, 480/2);
        painterSpeedPointer->rotate((lastSpeed + ((currentSpeed - lastSpeed)/2)) * 0.845f);
        speedPointerRenderer->render(painterSpeedPointer);
        painterSpeedPointer->end();

        QPainter *painterSpeedLabel = new QPainter(this);
        painterSpeedLabel->setOpacity(postOpacity);
        painterSpeedLabel->setPen(QColor(220, 220, 220));
        painterSpeedLabel->setFont(QFont("LCDMono", 55));
        painterSpeedLabel->drawText(QRect(580, 193 ,120,100),QString::number(currentLabelSpeed), Qt::AlignHCenter | Qt::AlignVCenter);
        painterSpeedLabel->end();

        QPainter *painterTimeLabel = new QPainter(this);
        painterTimeLabel->setOpacity(postOpacity);
        painterTimeLabel->setPen(QColor(220, 220, 220));
        painterTimeLabel->setFont(QFont("LCDMono", 20));
        painterTimeLabel->drawText(QRect(580, 30 ,120,30),time->currentTime().toString(), Qt::AlignHCenter | Qt::AlignVCenter);
        painterTimeLabel->end();

        if(currentSpeed <= 0){
            isInitClusterAnim_speedPointer = true;
            currentSpeed = 0;
            //qDebug() << "speedPointer_init_end";
        }
        speedTry = 0;

     }else{

        QPainter *painterOutline = new QPainter(this);
        outlineRenderer->render(painterOutline);
        painterOutline->end();

        QPainter *painterTimeLabel = new QPainter(this);
        painterTimeLabel->setPen(QColor(220, 220, 220));
        painterTimeLabel->setFont(QFont("LCDMono", 20));
        painterTimeLabel->drawText(QRect(580, 30 ,120,30),time->currentTime().toString(), Qt::AlignHCenter | Qt::AlignVCenter);
        painterTimeLabel->end();

        QPainter *painterSpeedPointer = new QPainter(this);
        painterSpeedPointer->translate(1280/2, 480/2);
        //qDebug() << "LS:" << infotaiment->getLastSpeed() << " Sp:" << infotaiment->getSpeed() <<  " Lerp:" <<(infotaiment->getLastSpeed() + ((infotaiment->getSpeed() - infotaiment->getLastSpeed())/2));

        infotaiment->setLastSpeed(infotaiment->getLastSpeed() + ((infotaiment->getSpeed() - infotaiment->getLastSpeed())/2));
        painterSpeedPointer->rotate(infotaiment->getLastSpeed() * 0.00845f);
        speedPointerRenderer->render(painterSpeedPointer);
        painterSpeedPointer->end();

        rS++;
        if(rS > 2){
            currentLabelSpeed = (int)infotaiment->getSpeed()/100;
            rS = 0;
        }

        //infotaiment->setSpeed(21300);
        /*qDebug() <<infotaiment->getSpeed();
        if(infotaiment->getSpeed() < 28000){
            infotaiment->setSpeed(speedTry);
            speedTry = speedTry + 100;
            currentLabelSpeed = (int)infotaiment->getSpeed()/100;

            if(infotaiment->getSpeed() >= 28000){
                infotaiment->setSpeed(0);
                speedTry = 0;
                qDebug()<<infotaiment->getSpeed();
            }

        }*/

        QPainter *painterSpeedLabel = new QPainter(this);
        painterSpeedLabel->setPen(QColor(220, 220, 220));
        painterSpeedLabel->setFont(QFont("LCDMono", 55));
        painterSpeedLabel->drawText(QRect(580, 193 ,120,100),QString::number(currentLabelSpeed), Qt::AlignHCenter | Qt::AlignVCenter);
        painterSpeedLabel->end();



        //ntWidgetManager->getNotificationWidgetList().at(0)->show();
    }
}
