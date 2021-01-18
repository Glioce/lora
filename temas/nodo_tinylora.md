## Nodo con TinyLoRa
Este tutorial usa la librería TinyLora y funciona  
https://learn.adafruit.com/the-things-network-for-feather  
https://github.com/adafruit/TinyLoRa  

Se modificó el ejemplo `tinylora_dht11` de la librería.  
Se agregaron las claves generadas por TTN, se usa el canal 0
y se asignaron los pines del sensor y del módulo RFM95.
```
// Pinout NodeMCU + RFM95
TinyLoRa lora = TinyLoRa(D1, D8, D2); //DIO0, NSS, RST

// pin the DHT22 is connected to
#define DHTPIN D4
DHT dht(DHTPIN, DHT11);

// ...

lora.setChannel(CH0);
```

![Diagrama de conexiones](../diagramas/LoRa%20node%20ESP8266%20-%20LED%20en%20GPIO16.png)
