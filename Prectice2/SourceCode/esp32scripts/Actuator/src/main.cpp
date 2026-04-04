#include "actuator.h"

Actuator actuator(
    "LIZ SAAVEDRA 5G",
    "melina5186804",
    "192.168.0.7",
    5000,
    13, 12, 14
);

void setup() {
    actuator.iniciar();
}

void loop() {
    actuator.loop();
}