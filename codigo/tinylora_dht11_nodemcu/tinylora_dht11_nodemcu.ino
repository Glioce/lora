// TinyLoRa DHT22 - ABP TTN Packet Sender (Multi-Channel)
// Tutorial Link: https://learn.adafruit.com/the-things-network-for-feather/using-a-feather-32u4
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright 2015, 2016 Ideetron B.V.
//
// Modified by Brent Rubell for Adafruit Industries, 2018
/************************** Configuration ***********************************/
#include <TinyLoRa.h>
#include <SPI.h>
#include "DHT.h"

// Visit your thethingsnetwork.org device console
// to create an account, or if you need your session keys.

// Network Session Key (MSB)
uint8_t NwkSkey[16] = { 0x8B, 0xF5, 0x24, 0x6D, 0xEE, 0xEA, 0xBD, 0x25, 0xB5, 0x3F, 0x36, 0x34, 0xF4, 0xFE, 0x32, 0x95 };

// Application Session Key (MSB)
uint8_t AppSkey[16] = { 0xCB, 0x10, 0x6E, 0xE7, 0x5D, 0x57, 0x91, 0xF7, 0x20, 0x73, 0x51, 0x15, 0x25, 0x6A, 0x2E, 0x5F };

// Device Address (MSB)
uint8_t DevAddr[4] = { 0x26, 0x02, 0x1E, 0xFF };

/************************** Example Begins Here ***********************************/
// Data Packet to Send to TTN
unsigned char loraData[4];

// How many times data transfer should occur, in seconds
const unsigned int sendInterval = 30;

// Pinout for Adafruit Feather 32u4 LoRa
//TinyLoRa lora = TinyLoRa(7, 8, 4);

// Pinout for Adafruit Feather M0 LoRa
//TinyLoRa lora = TinyLoRa(3, 8, 4);

// Pinout NodeMCU + RFM95
TinyLoRa lora = TinyLoRa(D1, D8, D2); //DIO0, NSS, RST

// pin the DHT22 is connected to
#define DHTPIN D4
DHT dht(DHTPIN, DHT11);

void setup()
{
  delay(2000);
  Serial.begin(74880);
  while (! Serial);
 
  // Initialize pin LED_BUILTIN as an output
  pinMode(LED_BUILTIN, OUTPUT); //GPIO16 - D0
  
  // Initialize LoRa
  Serial.print("Starting LoRa...");
  // define multi-channel sending
  lora.setChannel(CH6); //MULTI
  // set datarate
  lora.setDatarate(SF7BW125);
  if(!lora.begin())
  {
    Serial.println("Failed");
    Serial.println("Check your radio");
    while(true);
  }
  Serial.println("OK");

  // Initialize DHT
  dht.begin();
}

void loop()
{
   // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("");
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // encode float as int
  int16_t tempInt = round(t * 100);
  int16_t humidInt = round(h * 100);

  // encode int as bytes
  //byte payload[2];
  loraData[0] = highByte(tempInt);
  loraData[1] = lowByte(tempInt);
  
  loraData[2] = highByte(humidInt);
  loraData[3] = lowByte(humidInt);
  
  Serial.println("Sending LoRa Data...");
  lora.sendData(loraData, sizeof(loraData), lora.frameCounter);
  Serial.print("Frame Counter: ");Serial.println(lora.frameCounter);
  lora.frameCounter++;

  // blink LED to indicate packet sent
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.println("delaying...");
  delay(sendInterval * 1000);
}
