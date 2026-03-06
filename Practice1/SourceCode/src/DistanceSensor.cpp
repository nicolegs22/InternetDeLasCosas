#include "../include/DistanceSensor.h"    // header is one level up in include/


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

float DistanceSensor::medirDistancia() {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    unsigned long duracion = pulseIn(echoPin, HIGH, timeout);

    float distancia = duracion * soundSpeed / 2.0;

    return distancia;
}