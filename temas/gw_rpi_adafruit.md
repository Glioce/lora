## Gateway RPi Zero Adafruit
Este es el segundo tutorial que se ha seguido y funciona  
https://learn.adafruit.com/raspberry-pi-single-channel-lorawan-gateway  
https://github.com/adafruit/single_chan_pkt_fwd  

Se probó en RPi Zero W con RaspberryOS recién instalado.  
Los programas de prueba funcionan correctamente  
```
blinkatest.py
rfm9x_check.py
```
El programa rfm9x_check.py se puede modificar para que no dibuje
palabras encimadas en la pantalla OLED o se puede desconectar DIO0 del botón A.
En las pruebas se ha modificado para que no utilice la pantalla OLED.  

El programa del gateway ```lorawan_gateway.py``` funciona.
Cuando está encendido se muestra en TTN y recibe packets.  

Se pueden ajustar varios parámetros en `global_conf.json`.  
El valor de frecuencia parecía extraño ```"freq": 905100000```,
pero corresponde a la frecuencia del canal 6 905.1 MHz.
Se probó con ```"freq": 915000000```, pero no se recibieron packets.
RESET está asignado a un pin que no se conecta en las instrucciones,
pero no es importante. Cuando se ejecuta el programa gateway aparece un
mensaje que dice RESET unused.  

Modificaciones en el archivo  
```
    "freq": 905100000,
    "spread_factor": 7,
    "pin_nss": 11,
    "pin_dio0": 3,
    "pin_rst": 6
```
Ya se recibieron packets. El problema era la frecuencia de transmisión de los nodos,
debe ser 905.1 MHz, que corresponde al canal 6 en el rango de frecuencias que se usa en América.
También se ha usado la frecuencia 903.9 MHz que corresponde al canal 0.  

![Diagrama de conexiones](../diagramas/LoRa%20gateway%20RPi%20Zero.png)
