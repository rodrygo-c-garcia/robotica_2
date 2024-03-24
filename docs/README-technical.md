# [Practice ONE](https://github.com/rodrygo-c-garcia/robotica_2/tree/master/python_opencv/6_practice_1)

### **Descripción del ejercicio**

En este ejercicio, se utiliza OpenCV en Python para detectar rostros en tiempo real a través de una cámara. Se emplea el clasificador **haarcascade_frontalface_default.xml** proporcionado por OpenCV para la detección de rostros. Además, se envía información sobre la presencia y posición de los rostros a través de la comunicación serial a un dispositivo externo, un Arduino **MEGA 2560**. Dependiendo de la posición de los rostros detectados, se envían caracteres específicos ("**G**" para rostros a la derecha, "**B**" para rostros a la izquierda) para controlar LEDs externos (verde y azul, respectivamente). Si se detectan rostros en ambos lados, se envía un "**1**" para encender ambos LEDs.

### **Flujo del programa**

- **Inicialización de la cámara y el clasificador de rostros:** Se inicia la captura de video desde la cámara y se carga el clasificador de rostros preentrenado.

- **Detección y procesamiento de rostros:** Se detectan rostros en cada cuadro de video utilizando el clasificador haarcascade_frontalface_default.xml. Se dibujan círculos alrededor de los rostros detectados y se determina su posición (izquierda o derecha).

- **Envío de datos a través de la comunicación serial:** Se envían caracteres específicos ("G" o "B") a través de la comunicación serial para controlar LEDs externos, dependiendo de la posición de los rostros detectados. Si se detectan rostros en ambos lados, se envía un "1" para encender ambos LEDs.
