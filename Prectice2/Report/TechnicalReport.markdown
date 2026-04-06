Practica 2
Integrantes:
    -Gabriel Herrera
    -Nicole Gomez
    -Fernando Rodriguez

1.Requerimiento Funcionales 
    Los circuitos y códigos hechos requieren principalmente de la presencia de una red WiFi la cual permita conectar los tres dispositivos y enviar por medio de esta todos los datos de uno al otro, estos por medio de una comunicación TCP, la cual permite enviar y recibir datos de una entidad a otra.
    En este caso los tres elementos de la practica son:
        •	Actuador
        •	Sensor
        •	Servidor
    Este depende del protocolo integrado en el servido para mantener conexión, y además recibir ordenes de apagado y encendido, estas son las únicas señales de las que el actuador depende

    El sensor en su caso manda señales a su vez al servidor para estar activo, y luego identificar la longitud del objeto, este mandando señales del sensor ultrasónico al servidor para que este ultimo calcule la distancia final a usar.
    El servidor recibe y envía señales a tanto el sensor como el actuador, este obteniendo el tiempo de viaje de las ondas ultrasónicas para procesarlas y de esa manera calcular la distancia de los objetos. Por otro lado, envía un por medio de un mensaje codificado al actuador que led debe encender y cuales apagar, esto aclarado en los requerimientos no funcionales.
2.Requerimientos No Funcionales
    En cuanto al funcionamiento del proyecto este se divide en los siguientes puntos según los elementos del trabajo mismo:
    El actuador recibe datos del servidor para activar sus luces led, o apagarlas dependiendo del caso, siendo que se activan en los siguientes         
        rangos:
            Rango	        Color
             0 a 10	        Rojo
             10 a 20	    Azul
             20 a 30	    Verde
            Cualquier otro	Ninguno

    Este esta esperando en todo momento una orden del servidor y se mantendrá en el mismo estado hasta que una nueva orden se reciba del servidor. El actuador no tiene mas rangos debido a la característica demostrativa del proyecto y por ello se debe mantener su simplicidad de respuesta de datos, mientras que su fiabilidad se basa principalmente en la actualización del servidor, que esta puesta en cada 2 segundos para evitar overflow de datos.
    El Sensor en este caso manda los datos a la misma velocidad para de esa manera tampoco generar un overflow de estos en el servidor, con ello se deben también establecer que, si estabilidad se basa en la estructura, aunque simple, fiable del sensor ultrasónico.
    El servidor está limitado de manera que este no reciba datos a menos a que estén en un puerto especifico y que el mensaje entregado este dentro de los parámetros de lectura del mismo servidor, estos no tendrán un limite de funcionamiento, pero se verán afectados si es que el hardware no es mantenido, lo cual no es el caso debido a la aptitud demostrativa del trabajo.
3.




## *CONCLUSIÓN*

*Resumen:* Sistema cliente-servidor TCP/IP donde ESP32 sensor envía distancia a servidor Python, que evalúa reglas y envía comandos a ESP32 actuador para controlar LEDs RGB.

*Viabilidad:* Totalmente viable para proyectos IoT pequeños/medianos. Tecnología madura y probada.

*Puntos críticos:*
- Dependencia del servidor (punto único de falla)
- Latencia WiFi (20-100ms)
- Reconexión robusta necesaria
- Memoria limitada en ESP32

*Rendimiento esperado:*
- Muestreo: 10-50 lecturas/segundo
- Respuesta: 50-200ms
- Confiabilidad: 95-99%

*Escalabilidad:* JSON + IDs únicos permite múltiples dispositivos. Servidor multihilo soporta decenas de clientes.


## * RECOMENDACIONES *

### Implementación inicial
- *Simple primero* → TCP básico → registro → lógica → errores
- *Debugging:* Wireshark, monitor serial, scripts simuladores
- *Red:* IP fija, servidor Ethernet, canal WiFi limpio

### Robustez
- *Heartbeats:* ping/pong cada 10s (3 fallos = desconexión)
- *Timeouts:* ESP32 (5s), servidor (2s), non-blocking sockets
- *Almacenamiento:* EEPROM para última configuración y WiFi

### Protocolo
- *Versionado:* campo "version": "1.0"
- *Checksum:* para datos críticos
- *Colas:* máximo 3 comandos pendientes

### Lógica de control
- *Histéresis:* ±3cm para evitar rebotes (rojo <50cm, verde >60cm)
- *Modo seguro:* sin datos 3s → LEDs apagados
- *Calibración:* 10 lecturas iniciales para promedio base

### Monitoreo
- *Logs:* rotativos (10MB máx)
- *Panel:* endpoint HTTP simple con estado
- *Alertas:* distancia <10cm o desconexión >1 min

### Evitar problemas
- *Memoria ESP32:* StaticJsonDocument, evitar Strings, limpiar buffers
- *No bloqueos:* millis() en lugar de delay()
- *Anti-tormenta:* máximo 20 msgs/segundo

### Expansión futura
- *Hardware:* abstraer lectura del sensor
- *MQTT:* migrar si >10 dispositivos
- *Seguridad:* token, filtro IP, VPN

### Testing
- *Pruebas:* pérdida paquetes, reconexión, saturación, 48h continuo
- *Simulación:* scripts Python sin hardware

### Documentación
- *Viva:* diagrama flujo, códigos error, procedimientos
- *Diagnóstico:* script automático cada hora


## *RECOMENDACIÓN FINAL (Una frase)*

*Empieza con el prototipo más simple (TCP + eco) y añade complejidad gradualmente. La confiabilidad final depende más del código en ESP32 (reconexiones, timeouts, memoria) que del servidor Python.*
