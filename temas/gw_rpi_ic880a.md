## Gateway RPi iC880A
Este es el primer tutorial que se usó para configurar el gateway. Al final no funcionó  
https://www.thethingsnetwork.org/labs/story/building-a-ttn-gateway  

Es casi lo mismo que este tutorial  
https://github.com/ttn-zh/ic880a-gateway/wiki  

El programa no se compila correctamente.
Debe funcionar con una placa para crear un gateway multicanal ¿el módulo RFM95 lo soporta?  
https://wireless-solutions.de/products/lora-solutions-by-imst/radio-modules/ic880a-spi/  

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
