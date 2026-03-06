#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Arduino.h>

class LedController {
private:
    int redPin;
    int bluePin;
    int greenPin;

public:
    LedController(int red, int blue, int green);
    void begin();
    void actualizar(float distancia);
};

#endif