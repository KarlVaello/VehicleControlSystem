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

    boolean serialConnection = serial->open(QIODevice::ReadWrite);


    ntManager = new NotificationManager();

    qDebug() << "Types:" << QString::number(ntManager->getNotificationList().count()) << "\n";

    if(serialConnection){

        NotificationInfo *n01 = new NotificationInfo(0,"Serial Error");
        ntManager->apendNotification(n01);
        qDebug() << "Types:" << QString::number(ntManager->getNotificationList().count()) << "\n";
    }

    outlineRenderer = new QSvgRenderer(QString(":/img/outline.svg"));
    speedPointerRenderer = new QSvgRenderer(QString(":/img/speedPointer.svg"));
    notificationBannerRenderer = new QSvgRenderer(QString(":/img/notificationBanner.svg"));

    painterOutline = new QPainter (this);
    painterSpeedPointer = new QPainter (this);
    speedLabel = new QPainter(this);
    notBanner = new QPainter(this);
    notTitleLabel = new QPainter(this);

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


    notBanner->begin(this);
    notBanner->translate(200, 100);
    notBanner->scale(0.1f,0.1f);
    notificationBannerRenderer->render(notBanner);
    notBanner->end();


    notTitleLabel->begin(this);
    notTitleLabel->setPen(QColor(220, 220, 220));
    notTitleLabel->setFont(QFont("Arial", 8));
    notTitleLabel->drawText(QRect(250, 100 ,120,100),QString::fromStdString(ntManager->getNotificationList().at(0)->getTitle()));
    notTitleLabel->end();

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
