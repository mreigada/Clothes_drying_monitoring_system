# Sistema de monitoreo/estimación de secado de ropa
En este repositorio se encuentran los códigos fuentes del proyecto final para la asignatura Sistemas Embebidos (86.65). El mismo consiste en un sistema de estimación / monitoreo de secado de ropa mediante la medición de variables ambientales (temperatura, humedad) y el uso de un sensor de lluvia para detectar la posible ocurrencia de esta junto con una medición estimada de su intensidad.



## Características del sistema
- Sistema basado en la placa de desarrollo [WeMos D1 mini ESP8266](https://www.wemos.cc/en/latest/d1/d1_mini.html)
- Sensado de temperatura y humedad ambiente usando un sensor digital DHT11.
- Sensado de ocurrencia de lluvia e intensidad mediante sensor FC-37.
- Conexión Wi-Fi para posibilitar transmisión y recepción de datos desde y hacia la placa de control.
- Aplicación web para configuración del dispositivo por parte del usuario.



## Instalación
Para cargar el programa en la placa de desarrollo se requiere utilizar el plugin de Visual Studio Code [PlatformIO](https://platformio.org/). Una vez ya instalado, se debe proceder a abrir la carpeta como un proyecto y, teniendo la placa conectada mediante puerto USB a la computadora, cargar el código en ésta.



## Indicaciones para el uso sistema (provisorio)
1. Encender el sistema
2. Acceder desde un navegador web al puerto asignado (típicamente 192.168.1.45)
3. Elegir desde el menú desplegable el tipo de función a utilizar (estimación de tiempo de secado para interiores, estimación de tiempo de secado para exteriores, medición de variables ambientales)
4. Dar inicio a la estimación pulsando el botón "Start monitoring"
5. Según la opción elegida en el paso 4 se podrán ver en pantalla los resultados esperados, actualizandose de manera constante cada 15 segundos
6. En caso de querer volver al menú principal, pulsar el botón "Back to main menu"



## Documentación
La documentación tanto del código como del proyecto en sí estará disponible en el siguiente [enlace](https://github.com/mreigada/Clothes_drying_monitoring_system).
