#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include <Arduino.h>

class DistanceSensor {
private:
    int trigPin;
    int echoPin;
    float soundSpeed;
    unsigned long timeout;

public:
    DistanceSensor(int trig, int echo, float speed, unsigned long time);
    void begin();
    float medirDistancia();
};

#endif