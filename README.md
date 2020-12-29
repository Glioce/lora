# lora

Probar LoRaWAN  
Gateway: Raspberry Zero W + RFM95  
Nodos: ESP8266 + RFM95 + relay  

## Tutorial Gateway
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
palabras encimadas o se puede desconectar DIO0 del botón A.

El programa del gateway ```lorawan_gateway.py``` funciona.
Cuando está encendido se muestra en TTN y recibe packets.

Se pueden ajustar varios parámetros en ```global_conf.json```.  
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

## Tutorial Nodo
Este tutorial usa la librería TinyLora y funciona  
https://learn.adafruit.com/the-things-network-for-feather  
https://github.com/adafruit/TinyLoRa  

Se modificó el ejemplo ```tinylora_dht11``` de la librería.  
Se agregaron las claves generadas por TTN, se usa el canal 6
y se asignaron los pines del sensor y del módulo RFM95.
```
// Pinout NodeMCU + RFM95
TinyLoRa lora = TinyLoRa(D1, D8, D2); //DIO0, NSS, RST

// pin the DHT22 is connected to
#define DHTPIN D4
DHT dht(DHTPIN, DHT11);

// ...

lora.setChannel(CH6);
```

## Tutorial 1 Nodo - NO FUNCIONÓ
Este tutorial está enfocado en la placa Adafruit Feather y MCCI LoRaWAN LMIC library  
https://learn.adafruit.com/the-things-network-for-feather  
https://github.com/mcci-catena/arduino-lmic  
El ejemplo ttn_otaa no logra conectarse al gateway. Aparece esto en la consola  
```
06:33:36.561 -> 8890728: EV_TXSTART
06:33:42.866 -> 9284437: EV_JOIN_TXCOMPLETE: no JoinAccept
06:34:48.521 -> 13388293: EV_TXSTART
06:34:54.858 -> 13785217: EV_JOIN_TXCOMPLETE: no JoinAccept
```

El ejemplo ttn_abp no corre en el ESP8266 (se reinicia constantemente).

Estos temas mencionan formas de solucionar el problema de "no JoinSccept", pero el error tiene otra causa  
Incrementar tolerancia de reloj  
https://github.com/mcci-catena/arduino-lorawan/issues/74  
Cambiar spread factor y otras configuraciones  
https://www.thethingsnetwork.org/forum/t/feather-m0-ev-join-txcomplete-no-joinaccept-problem/38563/6  

Después se probó la librería TinyLora y funcionó. El problema era la frecuencia de
transmisión. En TinyLora se puede elegir el canal, se usó el el canal 6 (CH6) que
corresponde a la frecuencia 905.1 MHz, la misma frecuencia que escucha el gateway.
¿Cómo se puede elegir el canal en MCCI LoRaWAN LMIC library?


## Tutorial 1 Gateway
Primero se usaron estas instrucciones para el gateway. Al final no funcionó  
https://www.thethingsnetwork.org/labs/story/building-a-ttn-gateway  

Estas instrucciones funcionan (sección Software)  
```
$ gcc -o kitt kitt.c -l bcm2835
$ sudo ./kitt
```
Al ejecutar install.sh aparece un error  
```
$ sudo ./install.sh spi
```
Se ejecutan procesos en la RPi, pero no se conecta a TTN  
```
$ cd /var/log
$ sudo tail -f syslog
```
El código no se ha actualizado desde hace 4 años. 
Existen diferentes branches. ¿Alguna funciona mejor?  
https://github.com/galagaking/ic880a-gateway  

El repo usado en el tutorial es un fork de  
https://github.com/ttn-zh/ic880a-gateway  

## Otras librerías
Anatares LoRa.id  
https://github.com/antaresdocumentation/lorawan-loraid  

## Otros temas
Notas de "Primal Cortex"  
https://primalcortex.wordpress.com/tag/lorawan/  

Trabajar con bytes en TTN  
https://www.thethingsnetwork.org/docs/devices/bytes.html  

Diseño de antena  
https://www.thethingsnetwork.org/forum/t/diy-external-antenna-for-gateway/3011  

Raspberry pinout  
https://es.pinout.xyz  
