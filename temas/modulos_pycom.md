## Nodo y nano-gateway Pycom
Pycom tiene tutoriales sobre LoRa fáciles de seguir.  

Getting Started  
Probado en Lopy + Pysense  
https://docs.pycom.io/gettingstarted/  

Actualizar firmware  
No se ha actualizado. Usa MicroPython 1.18.2 (2019-11-26)  
https://docs.pycom.io/updatefirmware/device/  

Tutoriales LoRa  
La siguiente página tiene enlaces a ejemplos de código.  
https://docs.pycom.io/tutorials/networks/lora/  
Es más fácil seguir el siguiente tutorial  
En el tutorial se muestra cómo usar la extensión de TTN para Node-RED, 
esa estensión ha dejado de funcionar, es mejor utilizar la MQTT API  
https://core-electronics.com.au/tutorials/iot-with-lorawan-pycom-the-things-network-and-node-red.html  
Los dos tutoriales (nano-gw y node) que se mencionan en el tema anterior ayudaron a probar downlink con dos módulos Pycom.  
Los mismos tutoriales, pero en un formato menos amigable  
https://pycom.io/lopy-lorawan-nano-gateway-using-micropython-and-ttn/  

LoRa ABP (Authentication By Personalisation)  
Funciona cuando se usa la region LoRa.EU868, en la consola aparece b'' (datos recibidos).  
Si se cambia la región a LoRa.US915, aparece el error OSError: [Errno 95] EOPNOTSUPP  
https://docs.pycom.io/tutorials/networks/lora/lorawan-abp/  

Para hacer funcionar el nodo se deben desactivar todos los canales (0 a 72) y usar el data rate (DR) correcto  
https://forum.pycom.io/topic/1284/problem-pairing-otaa-node-to-nano-gateway-in-us-ttn  
Los DRs disponibles para cada región se indican en la especificación "Regional Parameters"  
https://lora-alliance.org/sites/default/files/2020-06/rp_2-1.0.1.pdf  
Los DRs para US915 se muestran en la página 30.  

Los nodos de TTN ya no se actualizan  
https://www.thethingsnetwork.org/docs/applications/nodered/  

Tutorial para Registrar Nano-Gateway  
https://core-electronics.com.au/tutorials/building-a-lorawan-nano-gateway-to-the-things-network.html  
https://docs.pycom.io/gettingstarted/registration/lora/ttn/#register-a-nano-gateway  
El código para obtener el ID se debe modificar  
```binascii.hexlify(wl.mac()[0])[:6] + 'FFFE' + binascii.hexlify(wl.mac()[0])[6:]```  

Fipy no se conectó al WiFi. Lopy sí se conecta.  
Se usó una versión actualizada del nano-gateway  
https://github.com/pycom/pycom-libraries/tree/master/examples/lorawan-nano-gateway  
Aparece un error en ```gateway.py```, se debe agregar la región como se muestra en este tema  
https://forum.pycom.io/topic/4413/nano-gateway-not-receiving-lorawan-packets  

Documentación de LoRa class Pycom  
https://docs.pycom.io/firmwareapi/pycom/network/lora/  
