Practica 2
Integrantes:
    -Gabriel Herrera
    -Nicole Gomez
    -Fernando Rodriguez
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
