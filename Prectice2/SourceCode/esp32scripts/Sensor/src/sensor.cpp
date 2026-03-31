#include "sensor.h"

Sensor::Sensor(const char* ssid, const char* password, const char* ip, int port, int trig, int echo) {
    this->ssid = ssid;
    this->password = password;
    this->serverIP = ip;
    this->serverPort = port;
    this->trigPin = trig;
    this->echoPin = echo;
}

void Sensor::iniciar() {
    Serial.begin(115200);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    conectarWiFi();
    conectarServidor();
}

void Sensor::loop() {
    if (!client.connected()) {
        Serial.println("Reconectando...");
        conectarServidor();
    }

    float distancia = medirDistancia();

    StaticJsonDocument<200> doc;
    doc["tipo"] = "sensor_data";
    doc["id"] = "ESP32_SENSOR_01";
    doc["distancia"] = distancia;

    String json;
    serializeJson(doc, json);
    client.println(json);

    Serial.println(distancia);

    delay(1000);
}

void Sensor::conectarWiFi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando WiFi...");
    }
}

void Sensor::conectarServidor() {
    if (client.connect(serverIP, serverPort)) {
        StaticJsonDocument<200> doc;
        doc["tipo"] = "registro";
        doc["id"] = "ESP32_SENSOR_01";
        doc["dispositivo_tipo"] = "sensor";

        String json;
        serializeJson(doc, json);
        client.println(json);
    }
}

float Sensor::medirDistancia() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duracion = pulseIn(echoPin, HIGH);
    return duracion * 0.034 / 2;
}