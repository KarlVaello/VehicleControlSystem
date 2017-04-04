#include "infotainment.h"

float Infotainment::getSpeed()
{
    return speed;
}

void Infotainment::setSpeed(float value)
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

float Infotainment::getLastSpeed()
{
    return lastSpeed;
}

void Infotainment::setLastSpeed(float value)
{
    lastSpeed = value;
}

Infotainment::Infotainment()
{

}
