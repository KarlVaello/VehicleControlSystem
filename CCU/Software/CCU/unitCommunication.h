#ifndef UNITCOMMUNICATION_H
#define UNITCOMMUNICATION_H


#include <QtSerialPort/QSerialPort>
#include <infotainment.h>
#include <QElapsedTimer>

class UnitCommunication
{
private:

    QElapsedTimer timer;


    Infotainment *infotaiment;


    QSerialPort *dataIn_port;
    QSerialPort *dataOut_port;

    QByteArray dataIn_data;
    QByteArray dataOut_data;
    QString dataIn_buffer;
    QString dataOut_buffer;
    QByteArray dataIn_bufferBytes;

    uint8_t b0 ;
    uint8_t b1 ;
    uint8_t b2 ;
    uint8_t b3 ;
    uint8_t b4 ;
    uint8_t b5 ;
    uint8_t b6 ;
    uint8_t b7 ;
    uint8_t b8 ;
    uint8_t b9 ;
    uint8_t b10 ;
    uint8_t b11 ;
    uint8_t b12 ;

    uint16_t ercSum;


    int goodDataCounter = 0;
    int badDataCounter = 0;
public slots:
    void sendData(char sourceID,char reciverID, char dataLenght, char rawData);
    void recanalizeMessage(QByteArray msg);
public:
    void readData();
    float merge_2hex8b_TO1hex16b(uint8_t h0 , uint8_t h1);
    UnitCommunication(Infotainment *infota);
    QSerialPort *getDataIn_port();
    QSerialPort *getDataOut_port();
};

#endif // UNITCOMMUNICATION_H
