#include "sensor.h"

Sensor sensor(
    "LIZ SAAVEDRA 5G",
    "melina5186804",
    "192.168.1.100",
    5000,
    5,   // trig
    18   // echo
);

void setup() {
    sensor.iniciar();
}

void loop() {
    sensor.loop();
}