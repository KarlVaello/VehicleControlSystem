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

Cluster::Cluster(QWidget *parent)
    : QWidget(parent)
{
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(0.05f);
    setWindowTitle(tr("Analog Clock"));


    resize(1280, 480);


    serial = new QSerialPort(this);
    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Description: " << serialPortInfo.description() << "\n";
        qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
        qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
        qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
        qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
    }

    serial->setPortName("COM8");
    serial->setBaudRate(9600);
    serial->setDataBits(QSerialPort::DataBits(8));
    serial->setStopBits(QSerialPort::StopBits(1));

    bool serialConnection = serial->open(QIODevice::ReadWrite);


    ntManager = new NotificationManager();

    ntWidgetManager = new NotificationWidgetManager();
    qDebug() << "Types:" << QString::number(ntManager->getNotificationList().count()) << "\n";

    if(!serialConnection){

        NotificationInfo *n01 = new NotificationInfo(0,"Serial Error");
        ntManager->apendNotification(n01);
        NotificationWidget *a = new NotificationWidget(ntManager->getNotificationList().at(0),250,200,this);

        ntWidgetManager->apendNotificationWidget(a);
        qDebug() << "Types:" << QString::number(ntManager->getNotificationList().count()) << "\n";
    }

    outlineRenderer = new QSvgRenderer(QString(":/img/outline.svg"));
    speedPointerRenderer = new QSvgRenderer(QString(":/img/speedPointer.svg"));
    notificationBannerRenderer = new QSvgRenderer(QString(":/img/notificationBanner.svg"));

    painterOutline = new QPainter (this);
    painterOutline->end();
    painterSpeedPointer = new QPainter (this);
    painterSpeedPointer->end(),
    speedLabel = new QPainter(this);
    speedLabel->end();


    serialBuffer = "";

    qDebug() << "Types:" << QString::number(ntManager->getNotificationList().count()) << "\n";

}

void Cluster::paintEvent(QPaintEvent *)
{

    connect(serial, &QSerialPort::readyRead, this, &Cluster::readData);

    painterOutline->begin(this);
    outlineRenderer->render(painterOutline);
    painterOutline->end();

    painterSpeedPointer->begin(this);
    painterSpeedPointer->translate(1280/2, 480/2);
    painterSpeedPointer->rotate((lastSpeed + ((currentSpeed - lastSpeed)/2)) * 0.845f);
    speedPointerRenderer->render(painterSpeedPointer);
    painterSpeedPointer->end();

    rS++;
    if(rS > 6){
        currentLabelSpeed = (int)currentSpeed;
        rS = 0;
    }

    speedLabel->begin(this);
    speedLabel->setPen(QColor(220, 220, 220));
    speedLabel->setFont(QFont("LCDMono", 50));
    speedLabel->drawText(QRect(580, 180 ,120,100),QString::number(currentLabelSpeed), Qt::AlignHCenter | Qt::AlignVCenter);
    speedLabel->end();


    ntWidgetManager->getNotificationWidgetList().at(0)->show();

}

void Cluster::readData()
{
    QStringList bufferSplit = serialBuffer.split(',');

    if(bufferSplit.length() < 2){
        serialData = serial->readAll();
        serialBuffer += QString::fromStdString( serialData.toStdString());
        //qDebug() << serialBuffer;
    }else{
        lastSpeed = currentSpeed;

        currentSpeed = bufferSplit[0].toFloat();
        //qDebug() << currentSpeed;
        serialBuffer = "";
        update();
    }
}
