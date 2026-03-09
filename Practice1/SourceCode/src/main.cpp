#include <Arduino.h>
#include "../include/DistanceSensor.h"
#include "../include/LedController.h"

const int TRIG_PIN = 5;
const int ECHO_PIN = 18;
const int ledPinRed = 12;
const int ledPinBlue = 14;
const int ledPinGreen = 27;
const float SOUND_SPEED = 0.034;
const unsigned long TIMEOUT = 30000;
DistanceSensor sensor(TRIG_PIN, ECHO_PIN, SOUND_SPEED, TIMEOUT);
LedController leds(ledPinRed, ledPinBlue, ledPinGreen);

void setup() {
    Serial.begin(115200);
    sensor.begin();
    leds.begin();
}

void loop() {
    float distance = sensor.measureDistance();
    Serial.print("Distance Measured:");
    Serial.print(distance);
    Serial.println(" cm");
    leds.update(distance);
    delay(500);
}