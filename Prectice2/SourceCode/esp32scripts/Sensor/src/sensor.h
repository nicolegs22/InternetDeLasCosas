#ifndef SENSOR_H
#define SENSOR_H

#include <WiFi.h>
#include <ArduinoJson.h>

class Sensor {
private:
    const char* ssid;
    const char* password;
    const char* serverIP;
    int serverPort;

    WiFiClient client;

    int trigPin;
    int echoPin;

public:
    Sensor(const char* ssid, const char* password, const char* ip, int port, int trig, int echo);

    void iniciar();
    void loop();

private:
    void conectarWiFi();
    void conectarServidor();
    float medirDistancia();
};

#endif