/**
 * Example of ABP device
 * Authors: 
 *        Ivan Moreno
 *        Eduardo Contreras
 *  June 2019
 * 
 * Editado para reportar voltaje de la batería.
 * Batería 18650 conectada a un divisor de voltaje.
 * La salida del divisor conectada a A0.
 */
#include <lorawan.h>

//ABP Credentials 
const char *devAddr = "26021EFF";
const char *nwkSKey = "8BF5246DEEEABD25B53F3634F4FE3295";
const char *appSKey = "CB106EE75D5791F720735115256A2E5F";

const unsigned long interval = 10000;    // 10 s interval to send message
unsigned long previousMillis = 0;  // will store last time message sent
unsigned int counter = 0;     // message counter

//char myStr[50];
char outStr[255];
byte recvStatus = 0;
char bytesToSend[2];

// Cuando se usa clase A, debe estar definido el pin que se 
// conecta a DIO1. De lo contrario el ESP se reinica constantemente.
const sRFM_pins RFM_pins = {
  .CS = D8,
  .RST = D2,
  .DIO0 = D1,
  .DIO1 = D2,
  .DIO2 = -1, //no es necesario definirlo
  .DIO5 = -1, //no es necesario definirlo
};

void setup() {
  // Setup loraid access
  Serial.begin(74880);
  delay(1000);
  if(!lora.init()){
    Serial.println("RFM95 not detected");
    delay(5000);
    return;
  }

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
}

void loop() {
  // Check interval overflow
  if(millis() - previousMillis > interval) {
    previousMillis = millis(); 

    //sprintf(myStr, "Counter-%d", counter); 
    uint16_t vRaw = analogRead(A0); //voltage raw

    Serial.print("Count: ");
    Serial.println(counter);
    Serial.print(", Voltage: ");
    Serial.println(vRaw, HEX);

    bytesToSend[0] = highByte(vRaw);
    bytesToSend[1] = lowByte(vRaw);
    
    //lora.sendUplink(myStr, strlen(myStr), 0, 1);
    lora.sendUplink(bytesToSend, 2, 0, 1);
    counter++;
  }

  recvStatus = lora.readData(outStr);
  if(recvStatus) {
    Serial.println(outStr);
  }
  
  // Check Lora RX
  lora.update();
}
