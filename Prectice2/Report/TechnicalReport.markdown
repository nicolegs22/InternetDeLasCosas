Práctica 2 – Sistema IoT con Sensor y Actuador
Integrantes
Gabriel Herrera
Nicole Gomez
Fernando Rodriguez

1. Requerimientos Funcionales

El sistema desarrollado requiere una red WiFi que permita la conexión entre tres componentes principales mediante comunicación TCP, lo que posibilita el envío y recepción de datos entre ellos.

Los elementos del sistema son:

        •   Actuador
        •	Sensor
        •	Servidor

El sensor ultrasónico mide la distancia de un objeto y envía estos datos al servidor.

El servidor recibe la información, la procesa y determina qué acción ejecutar en función de la distancia medida.

El actuador recibe comandos desde el servidor para encender o apagar un LED RGB según el rango de distancia.

El flujo de funcionamiento es el siguiente:

• El sensor mide la distancia.
• Envía los datos al servidor.
• El servidor procesa la información.
• El servidor envía un comando al actuador.
• El actuador ejecuta la acción (encender LED con un color específico).


3. Requerimientos No Funcionales
    El comportamiento del sistema se define mediante rangos de distancia que determinan el color del LED:       
        rangos:
            Rango	        Color
             0 a 10	        Rojo
             10 a 20	    Azul
             20 a 30	    Verde
             otros           Apagado

   Características adicionales:

El actuador mantiene el estado hasta recibir un nuevo comando.
El sensor envía datos cada 1 segundo para evitar saturación.
El sistema utiliza comunicación TCP confiable.
La estabilidad depende de:
Calidad de la red WiFi
Precisión del sensor ultrasónico
Capacidad del hardware

3. Arquitectura del Sistema

El sistema sigue una arquitectura cliente-servidor:

• Sensor → Cliente que envía datos
• Actuador → Cliente que recibe comandos
• Servidor → Nodo central que procesa lógica

4. Documentación del Código
Servidor (Python)
Clase: ServidorIoT

Gestiona la comunicación entre dispositivos.

Funciones principales:

• iniciar():
  Inicia el servidor y acepta conexiones.
• manejar_cliente():
  Recibe datos y los separa por mensajes.
• procesar_mensaje():
    • Registra dispositivos
    • Procesa datos del sensor
    • Determina color según distancia
• enviar_a_actuadores():
Envía comandos a todos los actuadores.

Clase: GestorClientes
Administra clientes conectados.

   • Registra dispositivos
   • Elimina desconectados
   • Filtra actuadores
   • Clase: Protocolo

Define formato de mensajes JSON:

{
  "tipo": "comando",
  "comando": "leds",
  "rgb": [255, 0, 0],
  "duracion": 1000
}

5. Dispositivos ESP32
Sensor

Funciones:

Mide distancia con ultrasonido
Envía datos al servidor

Fórmula utilizada:
        distancia = duracion x 0.034/2
Actuador

Funciones:

Recibe comandos JSON
Controla LED RGB
Envía confirmación al servidor

6. Resultados
El sistema funcionó correctamente, logrando una comunicación efectiva entre los dispositivos.
Pruebas realizadas
Prueba	     Distancia	      Resultado
1	         5 cm              	Rojo 
2	         15 cm             	Azul 
3	         25 cm	            Verde 
4	         40 cm          	Apagado 

Salida del servidor
Servidor IoT iniciado en 0.0.0.0:5000
[+] Registrado ESP32_ACTUADOR_01 (actuador)
[+] Registrado ESP32_SENSOR_01 (sensor)
ROJO     |   5.2 cm
AZUL     |  15.8 cm
VERDE    |  24.3 cm
APAGADO  |  42.1 cm



7. Pruebas del Sistema

Se realizaron diferentes pruebas para evaluar el comportamiento del sistema IoT en condiciones reales de funcionamiento. Estas pruebas se enfocaron en tres aspectos principales: integridad de los mensajes, velocidad de transmisión y estabilidad en uso prolongado.

7.1 Integridad de los mensajes enviados

Esta prueba tuvo como objetivo verificar que los datos enviados entre el sensor, el servidor y el actuador no presenten pérdidas ni alteraciones, incluso en un entorno con múltiples redes WiFi.

Metodología:

Se ejecutó el sistema en un entorno urbano con alta interferencia inalámbrica.
Se utilizó una herramienta de análisis de red (Wireshark) para observar los paquetes transmitidos.
Se monitorearon los mensajes enviados y recibidos entre dispositivos.

Resultados:

No se detectaron pérdidas de paquetes.
Los mensajes JSON llegaron completos y sin alteraciones.
No se observaron errores de comunicación.

Conclusión:
El uso del protocolo TCP garantiza la integridad de los datos, asegurando que los mensajes enviados sean recibidos correctamente.

7.2 Velocidad de envío de paquetes

Esta prueba evaluó el tiempo que tarda un mensaje en ser enviado desde el sensor hasta el servidor y procesado para generar una respuesta.

Datos obtenidos:

N	Diferencia (s)
1	0.79
2	0.60
3	0.66
4	0.77
5	0.80
6	0.81
7	0.81
8	0.82
9	0.91
10	0.85

Cálculo del promedio:

𝑥ˉ= 0.782

Cálculo del error promedio:

𝐸𝑟𝑟𝑜𝑟 ≈ 0.084

Resultados:

Latencia promedio baja (~0.78 s)
Variación pequeña entre mediciones

Conclusión:
El sistema presenta un tiempo de respuesta adecuado para aplicaciones IoT básicas, sin retrasos perceptibles a nivel humano.

7.3. Error debido al uso prolongado

Esta prueba evaluó el comportamiento del sistema durante ejecuciones prolongadas.

Metodología:

Se ejecutó el sistema continuamente durante varios minutos.
Se monitoreó el comportamiento del sensor, servidor y actuador.

Resultados:

Funcionamiento estable durante los primeros 10–11 minutos.
Posteriormente se observaron:
Errores de transmisión
Posible pérdida de conexión
Disminución en el rendimiento

Causas identificadas:

Saturación de memoria en el ESP32
Uso continuo del módulo WiFi
Falta de liberación de recursos

Conclusión:
El sistema no está optimizado para ejecución prolongada sin pausas. Se recomienda implementar mecanismos de gestión de memoria y reconexión automática.

8. Conclusiones

El sistema cumple correctamente su objetivo:

• Comunicación estable entre dispositivos
• Procesamiento en tiempo real
• Respuesta correcta del actuador
Conclusiones cuantitativas
•  Baja latencia
•  Error mínimo
• Alta confiabilidad en red local

9. Recomendaciones
• Implementar reconexión automática
•  Evitar uso continuo prolongado
•  Promediar mediciones del sensor
•  Optimizar uso de memoria

10. Anexos
    Estructura de archivos del proyecto:

    SourceCode/
    ├── server/
    │   ├── server.py
    │   ├── main.py
    │   ├── protocol.py
    │   ├── client_manager.py
    │   └── __pycache__/
    ├── esp32scripts/
    │   ├── Actuator/
    │   │   ├── src/
    │   │   │   ├── main.cpp
    │   │   │   ├── actuator.cpp
    │   │   │   └── actuator.h
    │   │   └── platformio.ini
    │   └── Sensor/
    │       ├── src/
    │       │   ├── main.cpp
    │       │   ├── sensor.cpp
    │       │   └── sensor.h
    │       └── platformio.ini

    Componentes utilizados:
        - 2x ESP32 (Wemos D1 R32 / ESP32 Dev Module)
        - 1x Sensor ultrasónico HC-SR04
        - 1x LED  
        - 3x Resistencias de 220Ω
        - Cables para la conexion
        - 2x Protoboard

    Esquema de conexiones:
        Sensor HC-SR04:
            VCC  → 5V ESP32
            GND  → GND
            TRIG → GPIO5
            ECHO → GPIO18

        LED RGB (ánodo común):
            Ánodo común → 3.3V ESP32
            Cátodo R → GPIO13 (con resistencia 220Ω)
            Cátodo G → GPIO12 (con resistencia 220Ω)
            Cátodo B → GPIO14 (con resistencia 220Ω)