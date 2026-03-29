from datetime import datetime

class Protocolo:
    @staticmethod
    def comando_led(color, duracion):
        colores = {
            "rojo": [255, 0, 0],
            "verde": [0, 255, 0],
            "amarillo": [255, 255, 0]
        }

        return {
            "tipo": "comando",
            "comando": "leds",
            "color": color,
            "rgb": colores.get(color, [255,255,255]),
            "duracion": duracion,
            "timestamp": datetime.now().isoformat()
        }