## Nodo con MCCI LMiC
Este tutorial está enfocado en la placa Adafruit Feather y MCCI LoRaWAN LMiC library  
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

Estos temas mencionan formas de solucionar el problema de "no JoinAccept", pero el error tiene otra causa  
Incrementar tolerancia de reloj  
https://github.com/mcci-catena/arduino-lorawan/issues/74  
Cambiar spread factor y otras configuraciones  
https://www.thethingsnetwork.org/forum/t/feather-m0-ev-join-txcomplete-no-joinaccept-problem/38563/6  

Después se probó la librería TinyLora y funcionó. El problema es la frecuencia de
transmisión. Se debe usar la misma frecuencia que escucha el gateway de 1 canal.
¿Cómo se puede elegir el canal en MCCI LoRaWAN LMIC library?

### Regreso a MCCI LMiC
Depués de probar varias alternativas que no funcionaron, se intentó usar esta librería otra vez.  

Este tema lista varias librerías LoRa compatibles con Arduino  
https://www.thethingsnetwork.org/forum/t/overview-of-lorawan-libraries-howto/24692  

MCCI LMiC se menciona en varios tutoriales y contiene un "full LoRaWAN stack".  
https://github.com/mcci-catena/arduino-lmic  

Tal vez conviene usar esta librería  
https://github.com/ricaun/SimpleLMIC  

Ya se usó la librería MCCI LMiC, pero no funcionó. El detalle es que está configurada
para usarse con un gw multicanal y solo se han utilizado gw con 1 canal. Se deben usar
valores fijos para canal (frecuencia), spread factor y bandwith.
Estos temas pueden ayudar  
https://github.com/matthijskooijman/arduino-lmic/issues/120  
https://www.thethingsnetwork.org/forum/t/can-lmic-1-6-be-set-up-to-use-a-single-channel-and-sf/5207  

Se moidifcaron los ejemplos de MCCI LMiC deshabilitando los canales como se muestra en el enlace anterior  
```
for(int i=0; i<9; i++) { // For EU; for US use i<71
    if(i != channel) {
        LMIC_disableChannel(i);
    }
}
// Set data rate (SF) and transmit power for uplink
LMIC_setDrTxpow(dr, 14);
```
El ejemplo ABP provoca que se reinicie el ESP.  
El ejemplo OTAA no logra "joinAccept".  

Se instaló SimpleLMIC y se modificó el ejemplo ```SimpleLMIC_ABP``` de igual forma.
Está vez funcionó, es extraño, se supone que usa casi el mismo código del ejemplo ABP anterior.  
No se reciben downlinks. ¿Se debe configurar la frecuencia de downlink?  

Primero se debe seleccionar la sub-banda de frecuencias  
```LMIC_selectSubBand(1);```

¿Qué signigica Adaptive Data Rate?  
https://www.thethingsnetwork.org/docs/lorawan/adaptive-data-rate.html  

Aquí se muestra otra forma de desactivar canales  
https://learn.sparkfun.com/tutorials/esp32-lora-1-ch-gateway-lorawan-and-the-things-network/turning-a-gateway-into-a-device  

No se ha logrado recibir downlinks. Se podría usar una librería más antigua:  
LMiC de matthijskooijman menciona que ha funcionado en ESP8266, MCCI LMiC no lo menciona  
https://github.com/matthijskooijman/arduino-lmic  
