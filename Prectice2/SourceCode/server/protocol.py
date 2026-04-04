from datetime import datetime

class Protocolo:
    @staticmethod
    def comando_led(rgb, duracion):
        """Crea comando para controlar LEDs RGB"""
        return {
            "tipo": "comando",
            "comando": "leds",
            "rgb": rgb,  # Lista de 3 enteros [R, G, B]
            "duracion": duracion,
            "timestamp": datetime.now().isoformat()
        }