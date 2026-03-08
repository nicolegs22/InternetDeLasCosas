Requerimientos Funcionales:

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

Resultados

Los resultados obtenidos durante la implementación del proyecto demostraron que el sistema es capaz de medir la distancia de un objeto utilizando un sensor ultrasónico y representar dicha información mediante indicadores luminosos (LEDs). Durante las pruebas, el sensor logró detectar variaciones de distancia y enviar los datos al microcontrolador, el cual procesó la información y activó el LED correspondiente según el rango programado. Cuando la distancia medida fue menor a 10 cm, el sistema encendió el LED rojo, indicando una proximidad muy cercana; para distancias entre 10 cm y 20 cm se activó el LED azul, representando una distancia intermedia; y para distancias entre 20 cm y 30 cm se encendió el LED verde, indicando que el objeto se encuentra a una distancia mayor. Cuando la distancia superó los 30 cm, ninguno de los LEDs se activó, señalando que no existe una proximidad relevante. Además, el sistema mostró un funcionamiento estable con un intervalo de actualización aproximado de 500 milisegundos, permitiendo una respuesta visual rápida ante cambios de distancia. Estos resultados evidencian que el programa cumple correctamente con el objetivo de integrar la medición de distancia con un sistema de señalización visual simple y eficiente mediante programación modular en un entorno de desarrollo basado en Arduino.

Conclusiones

El desarrollo del sistema permitió implementar un mecanismo de medición de distancia utilizando un sensor ultrasónico conectado a un microcontrolador, el cual procesa la información obtenida y activa diferentes indicadores visuales mediante LEDs. A través de la programación orientada a objetos se logró organizar el código en clases independientes, separando la lógica de medición del sensor (DistanceSensor) y el control de los indicadores luminosos (LedController), lo que facilita la comprensión, mantenimiento y escalabilidad del sistema. Además, el uso de distintos rangos de distancia para encender LEDs de diferentes colores permite representar de forma clara el nivel de proximidad de un objeto, demostrando la integración efectiva entre hardware y software para el desarrollo de aplicaciones simples de monitoreo y detección de distancia.

Recomendaciones

Se recomienda realizar varias mediciones consecutivas de distancia y calcular un promedio para mejorar la precisión del sistema, ya que los sensores ultrasónicos pueden presentar pequeñas variaciones en la lectura debido al ruido o a las condiciones del entorno. También sería conveniente incorporar una salida por el monitor serial para observar los valores de distancia en tiempo real durante las pruebas y facilitar la detección de posibles errores. Otra mejora posible es ajustar o ampliar los rangos de activación de los LEDs, dependiendo del uso específico del proyecto. Asimismo, se podría integrar otros dispositivos de alerta, como un buzzer o una pantalla LCD, para proporcionar más formas de notificación además de la señal visual. Finalmente, se recomienda optimizar el código reduciendo el uso de delay() o empleando técnicas de programación no bloqueante, lo que permitiría que el sistema sea más eficiente y pueda realizar múltiples tareas al mismo tiempo.

Anexos
En este anexo se incluyen imágenes relacionadas con el desarrollo y funcionamiento del sistema implementado. Las imágenes muestran el montaje del circuito, la conexión del sensor ultrasónico con el microcontrolador y los LEDs utilizados como indicadores de distancia. También se presentan capturas del funcionamiento del sistema durante las pruebas realizadas.

El propósito de estas imágenes es complementar la explicación del proyecto, permitiendo visualizar de manera más clara la estructura del hardware, la disposición de los componentes y el comportamiento del sistema cuando se detectan diferentes rangos de distancia.
