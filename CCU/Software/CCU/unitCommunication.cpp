#include "unitCommunication.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <infotainment.h>

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

    dataIn_port->setPortName("/dev/cu.usbmodemFA131");
    //dataIn_port->setPortName("COM8");
    dataIn_port->setBaudRate(115200);
    qDebug() << "open: " << dataIn_port->open(QIODevice::ReadOnly);
}


QSerialPort *UnitCommunication::getDataIn_port()
{
    return dataIn_port;
}

QSerialPort *UnitCommunication::getDataOut_port()
{
    return dataOut_port;
}

void UnitCommunication::readData(){

    dataIn_data = dataIn_port->readAll();
    //qDebug() <<" : "<<"dataIn_buffer: [" << dataIn_data.size() << "] "<< dataIn_data;

    if (dataIn_data.size() == 13){

        b0 = static_cast<int>(dataIn_data[0]);
        b1 = static_cast<int>(dataIn_data[1]);
        b2 = static_cast<int>(dataIn_data[2]);
        b3 = static_cast<int>(dataIn_data[3]);
        b4 = static_cast<int>(dataIn_data[4]);
        b5 = static_cast<int>(dataIn_data[5]);
        b6 = static_cast<int>(dataIn_data[6]);
        b7 = static_cast<int>(dataIn_data[7]);
        b8 = static_cast<int>(dataIn_data[8]);
        b9 = static_cast<int>(dataIn_data[9]);
        b10 = static_cast<int>(dataIn_data[10]);
        b11 = static_cast<int>(dataIn_data[11]);
        b12 = static_cast<int>(dataIn_data[12]);
        //qDebug() <<""<<"dataIn_buffer[" << dataIn_data.size() << "] "<< dataIn_data;

        //qDebug() <<  b0 << "/" <<  b1 << "/" <<  b2 << "/" <<  b3 << "/" <<  b4 << "/" <<  b5 <<
        //             "/" <<  b6 << "/" <<  b7 << "/"<<  b8 << "/"<<  b9 << "/"<<  b10 << "//" <<  b11 << "/"<<  b12 << "/";

        ercSum = b0 + b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8 + b9 + b10;

        //qDebug()<< "ercSum:  " << ercSum;

        QString ercSum_P1 = QString::number(b11,16) + QString::number(b12,16);
        //qDebug()<< "ercSum_P1  " << b11 << " - " << b12;
        qDebug()<< "ercSum_P1  " << ercSum_P1;

        bool bStatus2 = false;
        int nHex2 = ercSum_P1.toUInt(&bStatus2,16);

        //qDebug()<< "ercSum_P1 _ b11 b12: " << nHex2;

        if(ercSum  ==  nHex2){
            goodDataCounter++;
            QString a = QString::number(b4,16) + QString::number(b5,16);
            qDebug()<< "d1h y d2h: " << a;

            if (a.length() <4){
                a = a + "0";
                //qDebug()<< "CORRECTED: d1h y d2h: " << a;
            }

            bool bStatus = false;
            float nHex = a.toUInt(&bStatus,16);

           // qDebug()<< "final: " << nHex;
            if( b0 != 0){
                //"DATA NOT FOT ME - DO NOTHING";
            }else{ // DATA IS FOR ME
                switch (b1) {
                case 1:
                    switch (b2) {
                    case 0:
                        //infotaiment->setThrottle(b3);
                        infotaiment->setSpeed(nHex);
                        //qDebug() << "Speed: " << (nHex);
                        break;
                    case 1:
                        //infotaiment->setSpeed(d0);
                        break;
                    case 2:
                        //infotaiment->setThrottle(d0);
                        //infotaiment->setSpeed(d1);
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
            }
            dataIn_data = "";
        }else{
            qWarning()<< "BAD DATA!!!!!!";
            badDataCounter++;

        }
        int totalMessages = (goodDataCounter + badDataCounter);
        float errorCal = (100* (float)badDataCounter) / (float)totalMessages;

        qDebug() << "Total messages: " <<  totalMessages << " // good: " << goodDataCounter << " // " << "bad: " << badDataCounter << "// error%: " << errorCal << " %";
        qDebug()<< "-----------";
    }


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

