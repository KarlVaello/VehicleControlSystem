#ifndef UNITCOMMUNICATION_H
#define UNITCOMMUNICATION_H


#include <QtSerialPort/QSerialPort>
#include <infotainment.h>
#include "propulsionCommunication.h"


class UnitCommunication{
private:

    Infotainment *infotaiment;

    PropulsionCommunication *propulsionCom;


public:

    UnitCommunication(Infotainment *infota);
    void startCom(Infotainment *infota);

};

#endif // UNITCOMMUNICATION_H
