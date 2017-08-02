/*!
    \class PropulsionCommunication
    \brief The PropulsionCommunication class manage and proces all propulsion comunication (data in/out).
*/

#include "propulsionCommunication.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QTimer>
#include <infotainment.h>

/**
 * @brief PropulsionCommunication::PropulsionCommunication
 * @param parent = null
 * @param infota Infotaiment pointer to get and set all data
 */
PropulsionCommunication::PropulsionCommunication(QObject *parent, Infotainment *infota) : QObject(parent)
{
    infotaiment = infota;
    qDebug() << "PropulsionCommunication Contructor";
}


/**
 * @brief PropulsionCommunication::start init all port comunucation purpose
 * If ports fail automatically reports a CRITICAL ERROR
 *
 */
void PropulsionCommunication::start()
{
    propulsionCom_Read_port = new QSerialPort();

    propulsionCom_Read_port->setPortName("tty.wchusbserialfa130");
    propulsionCom_Read_port->setBaudRate(115200);
    propulsionCom_Read_port->open(QIODevice::ReadOnly);
    propulsionCom_Read_port->setDataBits(QSerialPort::Data8);
    qDebug() << "open: " << propulsionCom_Read_port->isOpen();

    if(propulsionCom_Read_port->isOpen()){
        propulsionCom_Read_port->clear();
        timer = new QTimer();
        timer->start(5); //5ns
        connect(timer,SIGNAL(timeout()),this,SLOT(propulsionCom_readData()));
    }else{
        qDebug() << "CRITICAL ERROR: Propulsion communication not working";
        //connect(timer,SIGNAL(timeout()),this,SLOT(fin()));

    }

}


/**
 * @fn propulsionCom_readData()
 * @brief PropulsionCommunication::propulsionCom_readData read all data incoming
 *          from propulsion modules.
 *        This function contains all decisions and manage all data from propulsion
 *          modules.
 */
void PropulsionCommunication::propulsionCom_readData(){

    propulsionCom_Read_data = propulsionCom_Read_port->readAll();
    qDebug() <<" : "<<"dataIn_buffer: [" << propulsionCom_Read_data.size() << "] "<< propulsionCom_Read_data;

    if (propulsionCom_Read_data.size() >= 13){

        pr_b0 = static_cast<uint8_t>(propulsionCom_Read_data[0]);
        pr_b1 = static_cast<uint8_t>(propulsionCom_Read_data[1]);
        pr_b2 = static_cast<uint8_t>(propulsionCom_Read_data[2]);
        pr_b3 = static_cast<uint8_t>(propulsionCom_Read_data[3]);
        pr_b4 = static_cast<uint8_t>(propulsionCom_Read_data[4]);
        pr_b5 = static_cast<uint8_t>(propulsionCom_Read_data[5]);
        pr_b6 = static_cast<uint8_t>(propulsionCom_Read_data[6]);
        pr_b7 = static_cast<uint8_t>(propulsionCom_Read_data[7]);
        pr_b8 = static_cast<uint8_t>(propulsionCom_Read_data[8]);
        pr_b9 = static_cast<uint8_t>(propulsionCom_Read_data[9]);
        pr_b10 = static_cast<uint8_t>(propulsionCom_Read_data[10]);
        pr_b11 = static_cast<uint8_t>(propulsionCom_Read_data[11]);
        pr_b12 = static_cast<uint8_t>(propulsionCom_Read_data[12]);
        //qDebug() <<""<<"dataIn_buffer[" << dataIn_data.size() << "] "<< dataIn_data;

        qDebug() <<  pr_b0 << "/" <<  pr_b1 << "/" <<  pr_b2 << "/" <<  pr_b3 << "/" <<  pr_b4 << "/" <<  pr_b5 <<
        "/" <<  pr_b6 << "/" <<  pr_b7 << "/"<<  pr_b8 << "/"<<  pr_b9 << "/"<<  pr_b10 << "//" <<  pr_b11 << "/"<<  pr_b12 << "/";

        pr_ercSum = pr_b0 + pr_b1 + pr_b2 + pr_b3 + pr_b4 + pr_b5 + pr_b6 + pr_b7 + pr_b8 + pr_b9 + pr_b10;

        if(pr_ercSum  ==  merge_2hex8b_TO1hex16b(pr_b11,pr_b12)){
             qDebug() << "goodData";
             pr_goodDataCounter++;

            if( pr_b0 == 0){ // bit reciverID -> 0x00 means CCU
                switch (pr_b1) { // sender ID
                case 1:
                    switch (pr_b2) {
                    case 0:
                        infotaiment->setSpeed(merge_2hex8b_TO1hex16b(pr_b4,pr_b5));
                        qDebug() << infotaiment->getSpeed();
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

                recanalizeMessage(propulsionCom_Read_data);
            }
            propulsionCom_Read_data = "";
        }else{
            qDebug() << "badData";

            pr_badDataCounter++;
        }
        int totalMessages = (pr_goodDataCounter + pr_badDataCounter);
        float errorCal = (100* (float)pr_badDataCounter) / (float)totalMessages;
        qDebug() << "Total messages: " <<  totalMessages << " // good: " << pr_goodDataCounter << " // " << "bad: " << pr_badDataCounter << "// error%: " << errorCal << " %";
    }
}

void PropulsionCommunication::recanalizeMessage(QByteArray message){

}
/**
 * @brief PropulsionCommunication::sendData
 * @param sourceID
 * @param reciverID
 * @param dataLenght
 * @param rawData
 */
void PropulsionCommunication::sendData(char sourceID,char reciverID, char dataLenght, char rawData){

    //buildData:
    // sourceID [5 bits] -> 00000 - 00001 - 00011 - ... 11111 (32 devices)
    // reciveID [5 bits] -> 00000 - 00001 - 00011 - ... 11111 (32 devices)
    // dataLenght [4 bits ] -> 0001 (8 bits) / 0001 (16 bits) / 0001 (32 bits) / 0001 (64 bits)
    // rawData [bits depends of dataLenght 0 - 64 bits (0-8 bytes)]
    //char *buildData = sourceID + reciverID + datalaLeng + rawData;
    char *buildData = new char(sourceID);
    propulsionCom_Write_port->write(buildData,5);
}
/**
 * @brief PropulsionCommunication::merge_2hex8b_TO1hex16b merge two numbers
 *          that normaly comes from an 16b hex and was separated on two 8b hex
 *          to be transmited.
 *        This return the original int (0-68000) that was split by for example a module.
 * @param h0
 * @param h1
 * @return merged hexadecimal number
 */
float PropulsionCommunication::merge_2hex8b_TO1hex16b(uint8_t h0 , uint8_t h1){
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

