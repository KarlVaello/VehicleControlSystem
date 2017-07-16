#ifndef PROPULSIONCOMMUNICATION_H
#define PROPULSIONCOMMUNICATION_H

#include <QtSerialPort/QSerialPort>
#include <QTimer>

class PropulsionCommunication: public QObject
{
    Q_OBJECT
private:

    QTimer *timer;

    QSerialPort *propulsionCom_Read_port;
    QSerialPort *propulsionCom_Write_port;



    QByteArray propulsionCom_Read_data;
    QByteArray propulsionCom_Write_data;
    QString propulsionCom_dataIn_buffer;
    QString propulsionCom_dataOut_buffer;
    QByteArray propulsionCom_dataIn_bufferBytes;

    uint8_t pr_b0 ;
    uint8_t pr_b1 ;
    uint8_t pr_b2 ;
    uint8_t pr_b3 ;
    uint8_t pr_b4 ;
    uint8_t pr_b5 ;
    uint8_t pr_b6 ;
    uint8_t pr_b7 ;
    uint8_t pr_b8 ;
    uint8_t pr_b9 ;
    uint8_t pr_b10 ;
    uint8_t pr_b11 ;
    uint8_t pr_b12 ;

    uint16_t pr_ercSum;

    int pr_goodDataCounter = 0;
    int pr_badDataCounter = 0;

public slots:
    //void doWork();
    void start();

public:
    PropulsionCommunication(QObject *parent = 0);

    //explicit PropulsionCommunication(qint32,QObject *parent = 0);
    qint32 myTime;

    void propulsionCom_readData();
    void sendData(char sourceID,char reciverID, char dataLenght, char rawData);
    void recanalizeMessage(QByteArray msg);

    float merge_2hex8b_TO1hex16b(uint8_t h0 , uint8_t h1);

};

#endif // PROPULSIONCOMMUNICATION_H
