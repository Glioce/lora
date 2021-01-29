/*******************************************
   Example of ABP device
   Authors:
          Ivan Moreno
          Eduardo Contreras
    June 2019

   Editado para reportar voltaje de una batería 18650. La batería está
   conectada a un divisor de voltaje y la salida del divisor conectada a A0.

   El tiempo de espera entre mensajes ya no se hace con millis().
   Se usa ESP.deepSleep para ahorrar energía.
 *********************************************/
#define DEBUG 1 //activar depuración por puerto serial
#include <lorawan.h>

//ABP Credentials
const char *devAddr = "26021EFF";
const char *nwkSKey = "8BF5246DEEEABD25B53F3634F4FE3295";
const char *appSKey = "CB106EE75D5791F720735115256A2E5F";

const unsigned long interval = 20e6; //tiempo en micro segundos
uint32_t counter; // message counter

char outStr[255]; //buffer para guardar mensaje de entrada
byte recvStatus = 0; //guarda el estado de recibido
char bytesToSend[2]; //bytes para enviar

// Cuando se usa clase A, debe estar definido el pin que se
// conecta a DIO1. De lo contrario el ESP se reinica constantemente.
const sRFM_pins RFM_pins = {
  .CS = D8,
  .RST = D4,
  .DIO0 = D1,
  .DIO1 = D2,
  .DIO2 = -1, //no es necesario definirlo
  .DIO5 = -1, //no es necesario definirlo
};
/* Otros pines
  D0 con RST
  D3 x
  D5 SCK
  D6 MISO
  D7 MOSI
*/

void setup() {
#if DEBUG
  Serial.begin(74880);
  //delay(1000);

  if (!lora.init()) {
    Serial.println("RFM95 not detected");
    //delay(5000);
    //return;
  }
#endif

  // Set LoRaWAN Class change CLASS_A or CLASS_C
  lora.setDeviceClass(CLASS_A);

  // Set Data Rate
  lora.setDataRate(SF7BW125);

  // set channel to random
  lora.setChannel(0); //MULTI

  // Put ABP Key and DevAddress here
  lora.setNwkSKey(nwkSKey);
  lora.setAppSKey(appSKey);
  lora.setDevAddr(devAddr);

  uint16_t vRaw = analogRead(A0); //voltage raw
  bytesToSend[0] = highByte(vRaw); //copiar valor a array
  bytesToSend[1] = lowByte(vRaw);
  lora.sendUplink(bytesToSend, 2, 0, 1); //enviar

  // obtener valor de contador en memoria RTC
  // incrementar valor y guardar de nuevo en memoria
  ESP.rtcUserMemoryRead(0, &counter, sizeof(counter));
  counter ++;
  ESP.rtcUserMemoryWrite(0, &counter, sizeof(counter));

  lora.update(); //Check Lora RX (esta línea podría ir antes)
  recvStatus = lora.readData(outStr); //ver si se reciben datos

#if DEBUG
  Serial.print("Count: ");
  Serial.println(counter);
  Serial.print(", Voltage: ");
  Serial.println(vRaw, HEX);

  if (recvStatus) {
    Serial.println(outStr);
  }
#endif

  // Dormir
  ESP.deepSleep(interval, RF_DISABLED);
  //RF_DEFAULT
  //RF_CAL
  //RF_NO_CAL
}

void loop() {}
