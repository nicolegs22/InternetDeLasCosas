#include <WiFi.h>
#include <ArduinoJson.h>

// 🔌 WIFI
const char* ssid = "TU_WIFI";
const char* password = "TU_PASSWORD";

// 🖥️ SERVER
const char* serverIP = "192.168.1.100";
const int serverPort = 5000;

WiFiClient client;

// 💡 Pines LED RGB
const int pinR = 13;
const int pinG = 12;
const int pinB = 14;

void setup() {
    Serial.begin(115200);

    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a WiFi...");
    }

    Serial.println("WiFi conectado");
    conectarServidor();
}

void conectarServidor() {
    if (client.connect(serverIP, serverPort)) {
        Serial.println("Conectado al servidor");

        StaticJsonDocument<200> doc;
        doc["tipo"] = "registro";
        doc["id"] = "ESP32_ACTUADOR_01";
        doc["dispositivo_tipo"] = "actuador";

        String json;
        serializeJson(doc, json);
        client.println(json);
    }
}

void loop() {
    if (!client.connected()) {
        Serial.println("Reconectando...");
        conectarServidor();
    }

    if (client.available()) {
        String mensaje = client.readStringUntil('\n');

        Serial.print("Mensaje recibido: ");
        Serial.println(mensaje);

        procesarComando(mensaje);
    }

    delay(10);
}

void procesarComando(String mensaje) {
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, mensaje);

    if (error) {
        Serial.println("Error JSON");
        return;
    }

    String tipo = doc["tipo"];

    if (tipo == "comando") {
        String comando = doc["comando"];

        if (comando == "leds") {
            int r = doc["rgb"][0];
            int g = doc["rgb"][1];
            int b = doc["rgb"][2];
            int duracion = doc["duracion"];

            // 💡 Encender LED
            analogWrite(pinR, r);
            analogWrite(pinG, g);
            analogWrite(pinB, b);

            delay(duracion);

            // Apagar
            analogWrite(pinR, 0);
            analogWrite(pinG, 0);
            analogWrite(pinB, 0);

            Serial.println("LED ejecutado");

            enviarConfirmacion(comando);
        }
    }
}

void enviarConfirmacion(String comando) {
    StaticJsonDocument<200> doc;

    doc["tipo"] = "comando_respuesta";
    doc["id"] = "ESP32_ACTUADOR_01";
    doc["comando"] = comando;
    doc["resultado"] = "ok";

    String json;
    serializeJson(doc, json);
    client.println(json);
}