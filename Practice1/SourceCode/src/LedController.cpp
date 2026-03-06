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

void LedController::actualizar(float distancia) {

    if(distancia < 10) {
        digitalWrite(redPin, HIGH);
        digitalWrite(bluePin, LOW);
        digitalWrite(greenPin, LOW);

    } else if(distancia >= 10 && distancia < 20) {
        digitalWrite(redPin, LOW);
        digitalWrite(bluePin, HIGH);
        digitalWrite(greenPin, LOW);

    } else if(distancia >= 20 && distancia < 30) {
        digitalWrite(redPin, LOW);
        digitalWrite(bluePin, LOW);
        digitalWrite(greenPin, HIGH);
    } else {
        digitalWrite(redPin, LOW);
        digitalWrite(bluePin, LOW);
        digitalWrite(greenPin, LOW);
    }
}