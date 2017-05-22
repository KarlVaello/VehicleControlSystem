#include "unitCommunication.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <infotainment.h>
#include <QElapsedTimer>

UnitCommunication::UnitCommunication(Infotainment *infota){

    infotaiment = infota;
    dataOut_port = new QSerialPort();
    dataIn_port = new QSerialPort();

    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Description: " << serialPortInfo.description() << "\n";
        qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
        qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
        qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
        qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
    }

    //dataOut_port->setPortName("/dev/cu.usbmodemFA131");
    //dataOut_port->setBaudRate(9600);
    //dataOut_port->setDataBits(QSerialPort::DataBits(64));
    //dataOut_port->setStopBits(QSerialPort::StopBits(1));
    //dataOut_port->open(QIODevice::WriteOnly);

    //dataIn_port->setPortName("/dev/cu.usbmodemFA131");
    dataIn_port->setPortName("COM16");
    dataIn_port->setBaudRate(115200);
    qDebug() << "open: " << dataIn_port->open(QIODevice::ReadOnly);
    dataIn_port->clear();
    dataIn_port->close();
    qDebug() << "open: " << dataIn_port->open(QIODevice::ReadOnly);
    timer.start();

}


QSerialPort *UnitCommunication::getDataIn_port(){
    return dataIn_port;
}

QSerialPort *UnitCommunication::getDataOut_port(){
    return dataOut_port;
}

void UnitCommunication::readData(){

    dataIn_data = dataIn_port->readAll();
    qDebug() <<" : "<<"dataIn_buffer: [" << dataIn_data.size() << "] "<< dataIn_data;

    if (dataIn_data.size() >= 13){

        b0 = static_cast<uint8_t>(dataIn_data[0]);
        b1 = static_cast<uint8_t>(dataIn_data[1]);
        b2 = static_cast<uint8_t>(dataIn_data[2]);
        b3 = static_cast<uint8_t>(dataIn_data[3]);
        b4 = static_cast<uint8_t>(dataIn_data[4]);
        b5 = static_cast<uint8_t>(dataIn_data[5]);
        b6 = static_cast<uint8_t>(dataIn_data[6]);
        b7 = static_cast<uint8_t>(dataIn_data[7]);
        b8 = static_cast<uint8_t>(dataIn_data[8]);
        b9 = static_cast<uint8_t>(dataIn_data[9]);
        b10 = static_cast<uint8_t>(dataIn_data[10]);
        b11 = static_cast<uint8_t>(dataIn_data[11]);
        b12 = static_cast<uint8_t>(dataIn_data[12]);
        //qDebug() <<""<<"dataIn_buffer[" << dataIn_data.size() << "] "<< dataIn_data;

        qDebug() <<  b0 << "/" <<  b1 << "/" <<  b2 << "/" <<  b3 << "/" <<  b4 << "/" <<  b5 <<
        "/" <<  b6 << "/" <<  b7 << "/"<<  b8 << "/"<<  b9 << "/"<<  b10 << "//" <<  b11 << "/"<<  b12 << "/";

        ercSum = b0 + b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8 + b9 + b10;

        if(ercSum  ==  merge_2hex8b_TO1hex16b(b11,b12)){
             qDebug() << "goodData";
            goodDataCounter++;

            if( b0 == 0){ // bit reciverID -> 0x00 means CCU
                switch (b1) { // sender ID
                case 1:
                    switch (b2) {
                    case 0:
                        //infotaiment->setSpeed(merge_2hex8b_TO1hex16b(b4,b5));
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
            }else{

                recanalizeMessage(dataIn_data);
            }
            dataIn_data = "";
        }else{
            qDebug() << "badData";

            badDataCounter++;
        }
        int totalMessages = (goodDataCounter + badDataCounter);
        float errorCal = (100* (float)badDataCounter) / (float)totalMessages;
        qDebug() << "Total messages: " <<  totalMessages << " // good: " << goodDataCounter << " // " << "bad: " << badDataCounter << "// error%: " << errorCal << " %";
    }


}
void UnitCommunication::recanalizeMessage(QByteArray message){

}

void UnitCommunication::sendData(char sourceID,char reciverID, char dataLenght, char rawData){

    //buildData:
    // sourceID [5 bits] -> 00000 - 00001 - 00011 - ... 11111 (32 devices)
    // reciveID [5 bits] -> 00000 - 00001 - 00011 - ... 11111 (32 devices)
    // dataLenght [4 bits ] -> 0001 (8 bits) / 0001 (16 bits) / 0001 (32 bits) / 0001 (64 bits)
    // rawData [bits depends of dataLenght 0 - 64 bits (0-8 bytes)]
    //char *buildData = sourceID + reciverID + datalaLeng + rawData;
    char *buildData = new char(sourceID);
    dataOut_port->write(buildData,5);
}

float UnitCommunication::merge_2hex8b_TO1hex16b(uint8_t h0 , uint8_t h1){
    float hexMerge = 0;

    QString secondHex2 = "";
    if (QString::number(h1,16).length()<2){
        secondHex2 = "0" + QString::number(h1,16);
    }else{
        secondHex2 = QString::number(h1,16);
    }
    QString a = QString::number(h0,16) + secondHex2;
    bool bStatus = false;
    hexMerge = a.toUInt(&bStatus,16);

    return hexMerge;
}
