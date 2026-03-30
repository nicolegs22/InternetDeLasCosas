#include <Arduino.h>
#include <string>

class Protocolo {
public:
    static String comando_led(String color, int duracion) {
        int r = 255, g = 255, b = 255;
        
        if (color == "rojo") {
            r = 255; g = 0; b = 0;
        } else if (color == "verde") {
            r = 0; g = 255; b = 0; 
        } else if (color == "amarillo") {
            r = 255; g = 255; b = 0;
        }
        
        String comando = "{\"tipo\":\"comando\",\"comando\":\"leds\",\"color\":\"" + color + 
                        "\",\"rgb\":[" + String(r) + "," + String(g) + "," + String(b) + 
                        "],\"duracion\":" + String(duracion) + "}";
        return comando;
    }
};