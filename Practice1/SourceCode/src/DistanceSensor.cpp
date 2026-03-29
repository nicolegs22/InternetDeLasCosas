#include "../include/DistanceSensor.h"    


DistanceSensor::DistanceSensor(int trig, int echo, float speed, unsigned long time) {
    trigPin = trig;
    echoPin = echo;
    soundSpeed = speed;
    timeout = time;
}

void DistanceSensor::begin() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float DistanceSensor::measureDistance() {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    unsigned long duration = pulseIn(echoPin, HIGH, timeout);

    float distance = duration * soundSpeed / 2.0;

    return distance;
}