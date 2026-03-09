#include "../include/LedController.h"

LedController::LedController(int red, int blue, int green) {
    redPin = red;
    bluePin = blue;
    greenPin = green;
}

void LedController::begin() {
    pinMode(redPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(greenPin, OUTPUT);
}

void LedController::update(float distance) {

    if(distance < 10) {
        digitalWrite(redPin, HIGH);
        digitalWrite(bluePin, LOW);
        digitalWrite(greenPin, LOW);

    } else if(distance >= 10 && distance < 20) {
        digitalWrite(redPin, LOW);
        digitalWrite(bluePin, HIGH);
        digitalWrite(greenPin, LOW);

    } else if(distance >= 20 && distance < 30) {
        digitalWrite(redPin, LOW);
        digitalWrite(bluePin, LOW);
        digitalWrite(greenPin, HIGH);
    } else {
        digitalWrite(redPin, LOW);
        digitalWrite(bluePin, LOW);
        digitalWrite(greenPin, LOW);
    }
}
