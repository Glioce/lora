/*
 * Funciona, pero cada uplink va junto a un downlink en la consola de TTN
 * Cuando se envían downlinks desde TTN no se reciben. 
 */

#include <SimpleLMIC.h>

const char *devAddr = "26021EFF";
const char *nwkSKey = "8BF5246DEEEABD25B53F3634F4FE3295";
const char *appSKey = "CB106EE75D5791F720735115256A2E5F";

const lmic_pinmap lmic_pins = {
  .nss = D8,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = LMIC_UNUSED_PIN,
  .dio = {D1, D2, LMIC_UNUSED_PIN} //DIO0, DIO1, DIO3
};

SimpleLMIC ttn;

#define DELAY 30000; //tiempo de retardo entre mensajes
unsigned long t = 0; //momento actual
unsigned long tSend = 0; //momento de enviar mensaje

void setup() {
  Serial.begin(74880);
  Serial.println();
  
  Serial.println(ttn.begin());
  ttn.setSubBand(2); //903.9 MHz (SF7? / 125 kHz?)
  ttn.onMessage(message); // callback function
  ttn.personalize(devAddr, nwkSKey, appSKey);

  //ttn.setLink(true); //Set LoRaWAN link
  //ttn.setAdr(false); //Adaptive Data Rate
  //ttn.setError(error); //Clock Error, default 5
  //ttn.debug(true); //Show the events on the Serial monitor

  // Define the single channel and data rate (SF) to use
  int channel = 8;
  int dr = DR_SF7;

  // Disable all channels, except for the one defined above. 
  // FOR TESTING ONLY!
  for(int i=0; i<72; i++) { // For EU; for US use i<71
    if(i != channel) {
      LMIC_disableChannel(i);
    }
  }

  // Set data rate (SF) and transmit power for uplink
  LMIC_setDrTxpow(dr, 14);
}

void loop() {
  ttn.loop();
  t = millis();
  if (!ttn.isBusy() and t >= tSend)
  {
    //delay(5000);
    Serial.println("Not Busy!");
    ttn.print("Hello");
    ttn.send();
    //delay(10000);
    tSend += DELAY;
  }
}

void message(uint8_t *payload, size_t size, uint8_t port)
{
  Serial.println("Received " + String(size) + " bytes on port " + String(port));
  switch (port) {
    case 1:
      break;
  }
}
