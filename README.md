# lora

Probar LoRaWAN  
Gateway: Raspberry Zero W + RFM95  
Nodos: ESP8266 + RFM95 + relay  

Gateways que han funcionado  
[Gateway RPi Zero Adafruit](./temas/gw_rpi_adafruit.md)  
[Gateway RPi Zero que permite downlinks]  

Nodos que han funcionado  
[Nodo con TinyLoRa](./temas/nodo_tinylora.md)  
[Nodo con Beelan_LoRaWAN](./temas/nodo_beelan.md)  

Nodo y gateway que funcionan usando módulos Pycom  
[Nodo y nano-gateway Pycom](./temas/modulos_pycom.md)  

Nodos que no han funcionado  
[Nodo con MCCI LMiC](./temas/nodo_mcci_lmic.md)  

Gateways que no han funcionado  
[Gateway RPi iC880A](./temas/gw_rpi_ic880a.md)  

## Bandas, canales y frecuencias
Tablas de frecuencias  
Las sub-bandas y las frecuencias de cada canal se pueden ver aquí  
https://www.baranidesign.com/faq-articles/2019/4/23/lorawan-usa-frequencies-channels-and-sub-bands-for-iot-devices  
https://www.thethingsnetwork.org/docs/lorawan/frequency-plans.html  
https://www.thethingsnetwork.org/docs/lorawan/frequencies-by-country.html  

## Gateway RPi Zero que permite downlinks
**Aún no tenemos un Gateway que permita downlinks usando RPi**  

## Usar MQTT en TTN
La extensión de TTN para Node-RED ya no funciona. La alternativa es usar MQTT.  

Guía para empezar  
https://www.thethingsnetwork.org/forum/t/mqtt-in-node-red-howto/39909  

Documentación  
https://www.thethingsnetwork.org/docs/applications/mqtt/quick-start.html  

Flujo de ejemplo para desencriptar payload  
https://flows.nodered.org/flow/845bb5b8cf788939dd261f472c289f77  

## Otras librerías que no implementan LoRaWAN
Anatares LoRa.id  
https://github.com/antaresdocumentation/lorawan-loraid  

LoraNow  
https://www.arduino.cc/reference/en/libraries/loranow/  

LoRa library by sandeep mistry  
https://randomnerdtutorials.com/esp32-lora-rfm95-transceiver-arduino-ide/  

## Ahorro de energía
Si el nodo funciona con batería debe usar la menor cantidad de energía posible.  
ESP82266 tiene 3 sleep-modes.  
https://www.espressif.com/sites/default/files/9b-esp8266-low_power_solutions_en_0.pdf  

Código prueba inicial de deep-sleep  
https://www.losant.com/blog/making-the-esp8266-low-powered-with-deep-sleep  

Tutorial con despertar con pulso de sensor PIR  
https://diyprojects.io/esp8266-deep-sleep-mode-test-wake-pir-motion-detector/#.YBNTH-nPzIU  
Menciona modos de configurar WiFi al salir de deep-sleep

## Otros temas
Tutorial extenso que muestra el registro de nodos y gws en TTN, 
LMiC, codificar y decodificar en TTN, MQTT usando Mosquitto  
https://gilberttanner.com/blog/getting-started-with-lorawan-and-the-things-network  

Tutorial que usa TTGO LORA32 y LMiC  
https://zaragozamakerspace.com/index.php/the-things-network-creacion-de-un-nodo-fisico/  

Notas de "Primal Cortex"  
https://primalcortex.wordpress.com/tag/lorawan/  

Trabajar con bytes en TTN  
https://www.thethingsnetwork.org/docs/devices/bytes.html  

Diseño de antena  
https://www.thethingsnetwork.org/forum/t/diy-external-antenna-for-gateway/3011  

Raspberry pinout  
https://es.pinout.xyz  
