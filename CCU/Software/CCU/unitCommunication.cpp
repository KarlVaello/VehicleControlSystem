#include "unitCommunication.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <infotainment.h>
#include <QElapsedTimer>
#include <propulsionCommunication.h>
#include <QThread>

UnitCommunication::UnitCommunication(Infotainment *infota){

    infotaiment = infota;

}

void UnitCommunication::startCom(Infotainment *infota){

    infotaiment = infota;

    QThread* propulsionThread = new QThread();

    propulsionCom = new PropulsionCommunication(0, infotaiment);

    propulsionCom->moveToThread(propulsionThread);
    QObject::connect(propulsionThread, SIGNAL(started()), propulsionCom, SLOT(start()));
    propulsionThread->start();

}


void UnitCommunication::discoverComPorts(){

    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Port Name: " << serialPortInfo.portName() << "\n";
        qDebug() << "Description: " << serialPortInfo.description() << "\n";
        qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
        qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
        qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
        qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
    }

}


