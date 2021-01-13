#include <lorawan.h>

//ABP Credentials 
const char *devAddr = "26021EFF";
const char *nwkSKey = "8BF5246DEEEABD25B53F3634F4FE3295";
const char *appSKey = "CB106EE75D5791F720735115256A2E5F";

const unsigned long interval = 10000;    // 10 s interval to send message
unsigned long previousMillis = 0;  // will store last time message sent
unsigned int counter = 0;     // message counter

char myStr[50];
char outStr[255];
byte recvStatus = 0;

// Si se usa clase C, solo es necesario conectar el pin DIO0.
// Se pueden enviar y recibir datos.
const sRFM_pins RFM_pins = {
  .CS = D8, //6,
  .RST = D3, //7,
  .DIO0 = D0, //8,
  .DIO1 = -1, //9,
  .DIO2 = -1,
  .DIO5 = -1,
};


void setup() {
  // Setup loraid access
  Serial.begin(74880);
  delay(1000);
  Serial.println("Start..");
  if(!lora.init()){
    Serial.println("RFM95 not detected");
    delay(5000);
    return;
  }

  // Set LoRaWAN Class change CLASS_A or CLASS_C
  lora.setDeviceClass(CLASS_C);

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

    sprintf(myStr, "Counter-%d", counter); 

    Serial.print("Sending: ");
    Serial.println(myStr);
    
    lora.sendUplink(myStr, strlen(myStr), 0, 1);
    counter++;
  }

  recvStatus = lora.readData(outStr);
  if(recvStatus) {
    Serial.print("====>> ");
    Serial.println(outStr);
  }
  
  // Check Lora RX
  lora.update();
}
