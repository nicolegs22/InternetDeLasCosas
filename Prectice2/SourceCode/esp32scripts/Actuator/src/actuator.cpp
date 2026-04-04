#include "actuator.h"

Actuator::Actuator(const char* ssid, const char* password, const char* ip, int port,
                   int r, int g, int b) {
    this->ssid = ssid;
    this->password = password;
    this->serverIP = ip;
    this->serverPort = port;
    this->pinR = r;
    this->pinG = g;
    this->pinB = b;
}

// El resto de tu código sigue igual...
void Actuator::iniciar() {
    Serial.begin(115200);
    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);
    
    conectarWiFi();
    conectarServidor();
}

void Actuator::loop() {
    if (!client.connected()) {
        conectarServidor();
        delay(1000);
        return;
    }

    if (client.available()) {
        String mensaje = client.readStringUntil('\n');
        procesarComando(mensaje);
    }
    
    delay(10);
}

void Actuator::conectarWiFi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n[WiFi] Conectado");
}

void Actuator::conectarServidor() {
    if (client.connect(serverIP, serverPort)) {
        StaticJsonDocument<200> doc;
        doc["tipo"] = "registro";
        doc["id"] = "ESP32_ACTUADOR_01";
        doc["dispositivo_tipo"] = "actuador";

        String json;
        serializeJson(doc, json);
        client.println(json);
        Serial.println("[ACTUADOR] Registrado en servidor");
    } else {
        Serial.println("[ACTUADOR] Error de conexión");
    }
}

void Actuator::procesarComando(String mensaje) {
    StaticJsonDocument<200> doc;
    if (deserializeJson(doc, mensaje)) return;

    if (doc["tipo"] == "comando" && doc["comando"] == "leds") {
        int r = doc["rgb"][0];
        int g = doc["rgb"][1];
        int b = doc["rgb"][2];
        int duracion = doc["duracion"];

        analogWrite(pinR, r);
        analogWrite(pinG, g);
        analogWrite(pinB, b);
        
        delay(duracion);
        
        analogWrite(pinR, 0);
        analogWrite(pinG, 0);
        analogWrite(pinB, 0);

        enviarConfirmacion("leds");
    }
}

void Actuator::enviarConfirmacion(String comando) {
    StaticJsonDocument<200> doc;
    doc["tipo"] = "comando_respuesta";
    doc["id"] = "ESP32_ACTUADOR_01";
    doc["comando"] = comando;
    doc["resultado"] = "ok";

    String json;
    serializeJson(doc, json);
    client.println(json);
}