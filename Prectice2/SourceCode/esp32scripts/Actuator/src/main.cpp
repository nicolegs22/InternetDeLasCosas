#include "actuator.h"

Actuator actuator(
    "CATOLAB",
    "sistemas2024",
    "192.168.1.100",
    5000,
    13, 12, 14
);

void setup() {
    actuator.iniciar();
}

void loop() {
    actuator.loop();
}