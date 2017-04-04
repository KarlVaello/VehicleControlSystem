#ifndef INFOTAINMENT_H
#define INFOTAINMENT_H


class Infotainment
{

private:

    int speed = 0;
    int lastSpeed = 0;
    int throttle = 0;

public:
    Infotainment();
    float getSpeed();
    void setSpeed(float value);
    int getThrottle();
    void setThrottle(int value);
    float getLastSpeed();
    void setLastSpeed(float value);
};

#endif // INFOTAINMENT_H
