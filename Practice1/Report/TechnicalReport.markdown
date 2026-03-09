Informe Tecnico
Integrantes:
    Gabriel Herrera
    Nicole Gomez
    Fernando Rodriguez

1 Requerimientos Funcionales:

El circuito construido para este proyecto ha sido hecho en una placa de desarrollo Wemos R1 32 con un microcontrolador ESP 32, junto a ello como actuadores se utilizaron 3 LED’s, estos representando la distancia medida desde el sensor, este ultimo siendo un sensor ultrasónico el cual esta conectado a la placa principal, otras conexiones fueron hechas en una placa de pruebas.
Sus rangos de funcionamientos son los siguientes:

Rango	Unidades

ROJO ENCENDIDO	X < 10 cm
BLUE ENCENDIDO	10 cm < X < 20 cm
GREEN ENCENDIDO	20 cm < X < 30 cm
TODOS APAGADOS	Cualquier otro valor
 
Estos valores fueron dados según las pruebas hechas con el sensor, estos basados principalmente en como el ultrasónico reacciona a la interferencia por un objeto extraño o por una gran distancia, todos estos datos se recolectaron por medio de un código aparte del principal, y además se utilizo en ambos casos la siguiente ecuación:
Distancia=  (velocidad del sonido*Tiempo de viaje de la señal)/2
Requerimientos no funcionales:
	El sistema construido puede ser implementado a otros proyectos
	El código es legible, modular y documentado.
	El sistema permite realizar cambios y desarrollar nuevas funciones sin perjudicar a las anteriores.

3 Documentacion del codigo
Clase: 
Distance Sensor
    atributos:
        -int trigPin; Pin encargado de enviar el pulso ultrasónico que inicia la medición.
        -int echoPin; Pin que recibe el pulso reflejado por el objeto.
        -float soundSpeed; Velocidad del sonido utilizada para calcular la distancia.
        -unsigned long timeout; Tiempo máximo de espera para recibir la señal de retorno.
    Metodos:
        DistanceSensor(...): Constructor que inicializa los parámetros necesarios para el funcionamiento del sensor.
        begin(): Configura los pines del sensor para su correcto funcionamiento en el microcontrolador.
            Proceso:
            Se encarga de inicializar la configuración de los pines del sensor ultrasónico en el microcontrolador. Para ello se utiliza la función pinMode() de la librería de Arduino, configurando el pin trigPin como salida (OUTPUT), ya que es el encargado de enviar el pulso ultrasónico, y el pin echoPin como entrada (INPUT), ya que recibe la señal reflejada cuando el sonido rebota en un objeto. Esta configuración es necesaria para que el sensor pueda emitir y recibir correctamente las señales utilizadas para medir la distancia.
        measureDistance(): Realiza la medición de la distancia calculando el tiempo que tarda el pulso ultrasónico en regresar al sensor.
            Proceso:
            Realiza el proceso de medición de distancia mediante el sensor ultrasónico. Primero se envía un pulso corto desde el pin trigPin utilizando digitalWrite() y delayMicroseconds(), lo que genera la onda ultrasónica. Luego, mediante la función pulseIn(), se mide el tiempo que tarda la señal reflejada en llegar al pin echoPin. Este tiempo se almacena en la variable duracion. Finalmente, la distancia se calcula multiplicando la duración del pulso por la velocidad del sonido (soundSpeed) y dividiendo el resultado entre dos, ya que la señal realiza un recorrido de ida y vuelta entre el sensor y el objeto. El valor calculado se devuelve como resultado de la función.

Clase: LedController
    Atributos:
        -int redPin: Pin del microcontrolador conectado al LED rojo, utilizado para indicar cuando el objeto está muy cerca del sensor.

        -int bluePin: Pin conectado al LED azul, que se activa cuando el objeto se encuentra a una distancia intermedia.

        -int greenPin: Pin conectado al LED verde, que indica que el objeto está a una distancia mayor dentro del rango configurado.
    Métodos:
        LedController(...): Constructor que inicializa los pines utilizados para controlar los LEDs.
        Proceso:
            Este método recibe como parámetros los pines donde están conectados los LEDs rojo, azul y verde, y los asigna a los atributos de la clase (redPin, bluePin, greenPin). De esta manera, la clase conoce qué pines del microcontrolador debe utilizar para controlar cada LED.

        begin(): Configura los pines de los LEDs para su funcionamiento como salidas.
        Proceso:
            Este método se encarga de preparar los pines del microcontrolador que controlan los LEDs. Para ello se utiliza la función pinMode() de la librería de Arduino, configurando los pines redPin, bluePin y greenPin como salidas (OUTPUT). Esto permite que el microcontrolador pueda enviar señales eléctricas para encender o apagar cada LED según la lógica del programa.

        update(float distance)Controla el encendido de los LEDs según la distance detectada por el sensor.
        Proceso:
            Este método recibe como parámetro la distance medida por el sensor ultrasónico y, a partir de ese valor, determina qué LED debe encenderse. Se utilizan estructuras condicionales if y else if para comparar la distance con distintos rangos definidos en el programa. Si la distance es menor a 10 cm, se enciende el LED rojo indicando que el objeto está muy cerca. Si la distance está entre 10 y 20 cm, se activa el LED azul, representando una distance intermedia. Si la distance está entre 20 y 30 cm, se enciende el LED verde, indicando que el objeto está más alejado. En caso de que la distance sea mayor o igual a 30 cm, todos los LEDs permanecen apagados. El control del encendido y apagado de los LEDs se realiza mediante la función digitalWrite().
Main
Objetos utilizados:
    -DistanceSensor sensor: Objeto encargado de gestionar el sensor ultrasónico y realizar la medición de la distancia entre el sensor y un objeto cercano.

    -LedController leds: Objeto responsable de controlar los LEDs del sistema, encendiendo el color correspondiente según la distancia detectada.
Funciones:

    setup(): Inicializa los componentes del sistema.

    Proceso:
        Esta función se ejecuta una sola vez al iniciar el microcontrolador. En ella se llama al método sensor.begin(), que configura los pines del sensor ultrasónico para su correcto funcionamiento, y al método leds.begin(), que configura los pines de los LEDs como salidas. De esta manera, todos los dispositivos quedan preparados para comenzar a operar.

    loop(): Ejecuta continuamente la lógica principal del sistema.

    Proceso:
        Esta función se ejecuta de manera repetitiva mientras el microcontrolador está encendido. En cada ciclo se obtiene la distancia detectada mediante sensor.measureDistance(), cuyo valor se guarda en la variable distance. Posteriormente, ese valor se envía al método leds.update(distance), que decide qué LED debe encenderse según el rango de distancia detectado. Finalmente, se utiliza delay(500) para realizar una pausa de medio segundo antes de repetir el proceso, permitiendo que las mediciones y la actualización de los LEDs se realicen de forma periódica.
5 Resultados

Los resultados obtenidos durante la implementación del proyecto demostraron que el sistema es capaz de medir la distancia de un objeto utilizando un sensor ultrasónico y representar dicha información mediante indicadores luminosos (LEDs). Durante las pruebas, el sensor logró detectar variaciones de distancia y enviar los datos al microcontrolador, el cual procesó la información y activó el LED correspondiente según el rango programado. Cuando la distancia medida fue menor a 10 cm, el sistema encendió el LED rojo, indicando una proximidad muy cercana; para distancias entre 10 cm y 20 cm se activó el LED azul, representando una distancia intermedia; y para distancias entre 20 cm y 30 cm se encendió el LED verde, indicando que el objeto se encuentra a una distancia mayor. Cuando la distancia superó los 30 cm, ninguno de los LEDs se activó, señalando que no existe una proximidad relevante. Además, el sistema mostró un funcionamiento estable con un intervalo de actualización aproximado de 500 milisegundos, permitiendo una respuesta visual rápida ante cambios de distancia. Estos resultados evidencian que el programa cumple correctamente con el objetivo de integrar la medición de distancia con un sistema de señalización visual simple y eficiente mediante programación modular en un entorno de desarrollo basado en Arduino.
Ademas de ello se detectaron distintas posibles anomalias en su funcionamiento, en este caso utilizar una superficie no recta y circular perjudica al sensado del objeto, con ello ademas viene el problema del rango minimo, este mismo es de 5 cm los cuales a menos de esa cantidad tiene descalibraciones las cuales no dan mediciones estables. Pero a a distancias de hasta 30 cm seran aptas.

6 Conclusiones

El desarrollo del sistema permitió implementar un mecanismo de medición de distancia utilizando un sensor ultrasónico conectado a un microcontrolador, el cual procesa la información obtenida y activa diferentes indicadores visuales mediante LEDs. A través de la programación orientada a objetos se logró organizar el código en clases independientes, separando la lógica de medición del sensor (DistanceSensor) y el control de los indicadores luminosos (LedController), lo que facilita la comprensión, mantenimiento y escalabilidad del sistema. Además, el uso de distintos rangos de distancia para encender LEDs de diferentes colores permite representar de forma clara el nivel de proximidad de un objeto, demostrando la integración efectiva entre hardware y software para el desarrollo de aplicaciones simples de monitoreo y detección de distancia.

7 Recomendaciones

Se recomienda realizar varias mediciones consecutivas de distancia y calcular un promedio para mejorar la precisión del sistema, ya que los sensores ultrasónicos pueden presentar pequeñas variaciones en la lectura debido al ruido o a las condiciones del entorno. También sería conveniente incorporar una salida por el monitor serial para observar los valores de distancia en tiempo real durante las pruebas y facilitar la detección de posibles errores. Otra mejora posible es ajustar o ampliar los rangos de activación de los LEDs, dependiendo del uso específico del proyecto. Asimismo, se podría integrar otros dispositivos de alerta, como un buzzer o una pantalla LCD, para proporcionar más formas de notificación además de la señal visual. Finalmente, se recomienda optimizar el código reduciendo el uso de delay() o empleando técnicas de programación no bloqueante, lo que permitiría que el sistema sea más eficiente y pueda realizar múltiples tareas al mismo tiempo.

8 Anexos
En este anexo se incluyen imágenes relacionadas con el desarrollo y funcionamiento del sistema implementado. Las imágenes muestran el montaje del circuito, la conexión del sensor ultrasónico con el microcontrolador y los LEDs utilizados como indicadores de distancia. También se presentan capturas del funcionamiento del sistema durante las pruebas realizadas.

El propósito de estas imágenes es complementar la explicación del proyecto, permitiendo visualizar de manera más clara la estructura del hardware, la disposición de los componentes y el comportamiento del sistema cuando se detectan diferentes rangos de distancia.
