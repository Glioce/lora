# lora

Probar LoRaWAN
Gateway: Raspberry Zero W + RFM95
Nodos: ESP8266 + RFM95

Primero se usaron estas instrucciones para el gateway  
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
