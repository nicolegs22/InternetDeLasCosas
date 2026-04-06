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
3. Documentación del Código
    Clase: ServidorIoT (Python)
        Servidor TCP que gestiona la comunicación entre sensores y actuadores.
            Atributos:
                host: Dirección IP donde escucha el servidor (0.0.0.0 para todas las interfaces)
                puerto: Puerto de comunicación (5000)
                server: Socket TCP del servidor
                gestor: Instancia de GestorClientes para manejar los clientes conectados

            Métodos:
                -iniciar(): Inicia el servidor, acepta conexiones y crea un hilo por cada cliente.
                    Proceso: Vincula el socket al host y puerto, comienza a escuchar y acepta conexiones entrantes. Por cada cliente, crea un hilo independiente para manejar su comunicación.

                -manejar_cliente(): Gestiona la comunicación con un cliente específico.
                    Proceso: Recibe datos del cliente, los acumula en un buffer y procesa mensajes completos separados por saltos de línea.

                -procesar_mensaje(): Analiza y procesa cada mensaje JSON recibido.
                    Proceso:
                    -Si es "registro": Registra el cliente en el gestor.
                    -Si es "sensor_data": Extrae la distancia, evalúa el rango, crea un comando RGB y lo envía a los actuadores.
                    -Si es "comando_respuesta": Confirma la ejecución del actuador.

                enviar_a_actuadores(): Envía un comando a todos los actuadores conectados.

    Clase: GestorClientes (Python)
        Administra el registro y seguimiento de los clientes conectados.

        Atributos:
            clientes: Diccionario que almacena los clientes usando su ID como clave.

        Métodos:
            registrar(): Añade un nuevo cliente al gestor.
                Proceso: Crea un objeto Cliente con ID, socket, dirección y tipo, y lo almacena en el diccionario.

            eliminar(): Remueve un cliente del gestor cuando se desconecta.
                Proceso: Busca el cliente por su socket y lo elimina del diccionario.

            obtener_actuadores(): Retorna una lista de todos los clientes de tipo "actuador".

    Clase: Protocolo (Python)
        Define la estructura de los mensajes del sistema.

        Métodos estáticos:
            comando_led(rgb, duracion): Crea un comando para controlar el LED RGB.
                Proceso: Construye un diccionario con tipo "comando", comando "leds", valores RGB, duración y timestamp.

        Formato del mensaje:
            {
                "tipo": "comando",
                "comando": "leds",
                "rgb": [255, 0, 0],
                "duracion": 1000,
                "timestamp": "2024-01-01T12:00:00"
            }

    Clase: Sensor (ESP32 - C++)
        Gestiona el sensor ultrasónico y envía mediciones al servidor.

        Atributos:
            ssid, password: Credenciales de la red WiFi
            serverIP, serverPort: Dirección del servidor
            trigPin, echoPin: Pines conectados al sensor ultrasónico
            client: Cliente WiFi para comunicación TCP

        Métodos:
            iniciar(): Configura el sistema y establece conexiones.
                Proceso: Inicializa Serial, configura pines del sensor, conecta a WiFi y se registra en el servidor.

            loop(): Ejecución principal del sensor.
                Proceso: Verifica la conexión con el servidor, mide la distancia, envía los datos en formato JSON y espera 1 segundo.

            medirDistancia(): Realiza la medición ultrasónica.
                Proceso:
                    - Envía un pulso de 10μs por el pin trigPin
                    - Mide la duración del pulso de retorno con pulseIn()
                    - Calcula distancia = duración * 0.034 / 2

            conectarWiFi(): Conecta a la red WiFi.
            conectarServidor(): Establece conexión TCP y se registra.

    Clase: Actuator (ESP32 - C++)
        Controla el LED RGB según comandos recibidos del servidor.

        Atributos:
            ssid, password: Credenciales WiFi
            serverIP, serverPort: Dirección del servidor
            pinR, pinG, pinB: Pines del LED RGB
            client: Cliente WiFi

        Métodos:
            iniciar(): Configura pines y establece conexiones.
                Proceso: Inicializa Serial, configura pines como salida PWM, conecta a WiFi y se registra.

            loop(): Escucha comandos del servidor.
                Proceso: Verifica conexión, procesa mensajes entrantes.

            procesarComando(): Ejecuta comandos recibidos.
                Proceso:
                    - Parsea el JSON del comando
                    - Extrae valores RGB y duración
                    - Aplica PWM a los pines con analogWrite()
                    - Espera la duración especificada
                    - Apaga el LED
                    - Envía confirmación al servidor

            enviarConfirmacion(): Notifica al servidor que el comando se ejecutó.

    Archivo main.py
        Punto de entrada del servidor.

        Proceso:
            - Crea una instancia de ServidorIoT
            - Inicia el servidor
            - Maneja la interrupción de teclado (Ctrl+C) para cerrar gracefulmente

    Archivo main.cpp (Sensor)
        Punto de entrada del ESP32 sensor.

        Objetos:
            sensor: Instancia de la clase Sensor con configuración WiFi, IP del servidor (192.168.0.13:5000), trig=5, echo=18.

        Funciones:
            setup(): Llama a sensor.iniciar()
            loop(): Llama a sensor.loop() repetidamente

    Archivo main.cpp (Actuador)
        Punto de entrada del ESP32 actuador.

        Objetos:
            actuator: Instancia con pines RGB en 13, 12, 14

        Funciones:
            setup(): Llama a actuator.iniciar()
            loop(): Llama a actuator.loop() repetidamente



5. Resultados
    Los resultados obtenidos durante la implementación demostraron que el sistema cliente-servidor funciona correctamente. El sensor ultrasónico logra medir distancias con precisión y enviar los datos al servidor a través de WiFi. El servidor procesa las mediciones y envía comandos al actuador, que controla el LED RGB según el rango de distancia programado.

    Pruebas realizadas:

    Prueba    Distancia (cm)    Color Esperado    Resultado
    1         5                 ROJO              ✅ Correcto
    2         15                AZUL              ✅ Correcto
    3         25                VERDE             ✅ Correcto
    4         40                APAGADO           ✅ Correcto
    5         8                 ROJO              ✅ Correcto
    6         18                AZUL              ✅ Correcto

    Salida del servidor durante pruebas:

    Servidor IoT iniciado en 0.0.0.0:5000
    --------------------------------------------------
    [+] Registrado ESP32_ACTUADOR_01 (actuador)
    [+] Registrado ESP32_SENSOR_01 (sensor)
    ROJO     |   5.2 cm
    AZUL     |  15.8 cm
    VERDE    |  24.3 cm
    APAGADO  |  42.1 cm

    Anomalías detectadas:
        - El sensor ultrasónico tiene un rango mínimo de 2-4 cm, por debajo del cual las mediciones son inestables.
        - Superficies no planas o angulosas afectan la reflexión del ultrasonido, generando lecturas erróneas.
        - La conexión WiFi puede interrumpirse si hay interferencia, requiriendo reconexión automática.
        - La latencia de red puede causar pequeños retrasos entre la medición y la activación del LED.

6. Conclusiones
    El desarrollo del sistema permitió implementar una arquitectura cliente-servidor completa para la practica, donde dos dispositivos ESP32 se comunican con un servidor central en Python. 

    Logros principales:
        - Comunicación bidireccional entre sensor, servidor y actuador.
        - Procesamiento concurrente de múltiples clientes mediante hilos.
        - Código modular y orientado a objetos en ambos lenguajes (Python y C++).
        - Control de LED basado en rangos de distancia.

    El sistema cumple con el objetivo de medir distancia y representarla visualmente mediante colores.

7. Recomendaciones

    Se recomienda realizar varias pruebas del sensor y tomar más de una medición antes de usar el valor final, ya que en algunos momentos las lecturas pueden variar un poco. También es importante verificar constantemente la conexión del ESP32, asegurándose de que pueda reconectarse si el WiFi o el servidor fallan durante las pruebas.

    Durante el desarrollo, es útil observar los datos en tiempo real (por ejemplo en el monitor serial) para detectar errores o comportamientos inesperados. Además, se podría considerar hacer una pequeña interfaz o visualización simple para entender mejor cómo está funcionando el sistema mientras se ejecuta.

    Por otro lado, al trabajar con el actuador, es recomendable evitar pausas largas que detengan el programa, ya que esto puede impedir que responda rápidamente a nuevos comandos. Finalmente, sería conveniente permitir ajustar fácilmente los rangos de distancia y el comportamiento de los LEDs sin tener que modificar todo el código, facilitando así futuras pruebas y mejoras del sistema.

8. Anexos
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