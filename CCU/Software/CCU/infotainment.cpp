#include "infotainment.h"

int Infotainment::getSpeed()
{
    return speed;
}

void Infotainment::setSpeed(int value)
{
    speed = value;
}

int Infotainment::getThrottle()
{
    return throttle;
}

void Infotainment::setThrottle(int value)
{
    throttle = value;
}

int Infotainment::getLastSpeed()
{
    return lastSpeed;
}

void Infotainment::setLastSpeed(int value)
{
    lastSpeed = value;
}

Infotainment::Infotainment(){}
