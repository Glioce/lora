/*******************************************************************************
   Copyright (c) 2015 Thomas Telkamp and Matthijs Kooijman
   Copyright (c) 2018 Terry Moore, MCCI

   Permission is hereby granted, free of charge, to anyone
   obtaining a copy of this document and accompanying files,
   to do whatever they want with them without any restriction,
   including, but not limited to, copying, modification and redistribution.
   NO WARRANTY OF ANY KIND IS PROVIDED.

   This example sends a valid LoRaWAN packet with payload "Hello,
   world!", using frequency and encryption settings matching those of
   the The Things Network.

   This uses OTAA (Over-the-air activation), where where a DevEUI and
   application key is configured, which are used in an over-the-air
   activation procedure where a DevAddr and session keys are
   assigned/generated for use with all further communication.

   Note: LoRaWAN per sub-band duty-cycle limitation is enforced (1% in
   g1, 0.1% in g2), but not the TTN fair usage policy (which is probably
   violated by this sketch when left running for longer)!

   To use this sketch, first register your application and device with
   the things network, to set or generate an AppEUI, DevEUI and AppKey.
   Multiple devices can use the same AppEUI, but each device has its own
   DevEUI and AppKey.

   Do not forget to define the radio type correctly in
   arduino-lmic/project_config/lmic_project_config.h or from your BOARDS.txt.

 *******************************************************************************/

#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

//
// For normal use, we require that you edit the sketch to replace FILLMEIN
// with values assigned by the TTN console. However, for regression tests,
// we want to be able to compile these scripts. The regression tests define
// COMPILE_REGRESSION_TEST, and in that case we define FILLMEIN to a non-
// working but innocuous value.
//
/*
  #ifdef COMPILE_REGRESSION_TEST
  # define FILLMEIN 0
  #else
  # warning "You must replace the values marked FILLMEIN with real values from the TTN control panel!"
  # define FILLMEIN (#dont edit this, edit the lines that use FILLMEIN)
  #endif
*/

// This EUI must be in little-endian format, so least-significant-byte
// first. When copying an EUI from ttnctl output, this means to reverse
// the bytes. For TTN issued EUIs the last bytes should be 0xD5, 0xB3,
// 0x70.
// APPEUI msb { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x03, 0xA5, 0x85 }
// APPEUI lsb { 0x85, 0xA5, 0x03, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 }
//appeui2 { 0xFB, 0xA7, 0x03, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 }
static const u1_t PROGMEM APPEUI[8] = { 0xFB, 0xA7, 0x03, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 };
void os_getArtEui (u1_t* buf) {
  memcpy_P(buf, APPEUI, 8);
}

// This should also be in little endian format, see above.
// DEVEUI msb { 0x98, 0xF4, 0xAB, 0x00, 0x00, 0xDA, 0xE1, 0x3E }
// DEVEUI lsb { 0x3E, 0xE1, 0xDA, 0x00, 0x00, 0xAB, 0xF4, 0x98 }
// lolin dev msb { 0x80, 0x7D, 0x3A, 0x00, 0x00, 0x6E, 0x63, 0x2F }
// lolin dev lsb { 0x2F, 0x63, 0x6E, 0x00, 0x00, 0x3A, 0x7D, 0x80 }
//deveui2 { 0x80, 0x7D, 0x3A, 0x00, 0x00, 0x6E, 0x63, 0x2F }
static const u1_t PROGMEM DEVEUI[8] = { 0x80, 0x7D, 0x3A, 0x00, 0x00, 0x6E, 0x63, 0x2F };
void os_getDevEui (u1_t* buf) {
  memcpy_P(buf, DEVEUI, 8);
}

// This key should be in big endian format (or, since it is not really a
// number but a block of memory, endianness does not really apply). In
// practice, a key taken from ttnctl can be copied as-is.
// AK msb { 0x20, 0x6D, 0xEF, 0x73, 0x4D, 0x5A, 0xD3, 0xBB, 0xF6, 0x0A, 0x08, 0xE5, 0x27, 0xE7, 0xE1, 0x8C }
// AK lsb { 0x8C, 0xE1, 0xE7, 0x27, 0xE5, 0x08, 0x0A, 0xF6, 0xBB, 0xD3, 0x5A, 0x4D, 0x73, 0xEF, 0x6D, 0x20 }
//akey2 { 0x36, 0xC5, 0xBF, 0x29, 0x28, 0x49, 0x79, 0x00, 0xB3, 0xD6, 0xB6, 0xDB, 0x7E, 0x77, 0x1B, 0x88 }
static const u1_t PROGMEM APPKEY[16] = { 0x36, 0xC5, 0xBF, 0x29, 0x28, 0x49, 0x79, 0x00, 0xB3, 0xD6, 0xB6, 0xDB, 0x7E, 0x77, 0x1B, 0x88 };
void os_getDevKey (u1_t* buf) {
  memcpy_P(buf, APPKEY, 16);
}

static uint8_t mydata[] = "Hello";
static osjob_t sendjob;

// Schedule TX every this many seconds (might become longer due to duty
// cycle limitations).
const unsigned TX_INTERVAL = 30;

// Pin mapping
const lmic_pinmap lmic_pins = {
  .nss = D8,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = LMIC_UNUSED_PIN,
  .dio = {D1, D2, LMIC_UNUSED_PIN},
}; //A0 //LMIC_UNUSED_PIN

// Define the single channel and data rate (SF) to use
int channel = 8;
int dr = DR_SF7;

// Disables all channels, except for the one defined above, and sets the
// data rate (SF). This only affects uplinks; for downlinks the default
// channels or the configuration from the OTAA Join Accept are used.
//
// Not LoRaWAN compliant; FOR TESTING ONLY!
//
void forceTxSingleChannelDr() {
    for(int i=0; i<72; i++) { // For EU; for US use i<71
        if(i != channel) {
            LMIC_disableChannel(i);
        }
    }
    // Set data rate (SF) and transmit power for uplink
    LMIC_setDrTxpow(dr, 14);
}

void printHex2(unsigned v) {
  v &= 0xff;
  if (v < 16)
    Serial.print('0');
  Serial.print(v, HEX);
}

void onEvent (ev_t ev) {
  Serial.print(os_getTime());
  Serial.print(": ");
  switch (ev) {
    case EV_SCAN_TIMEOUT:
      Serial.println(F("EV_SCAN_TIMEOUT"));
      break;
    case EV_BEACON_FOUND:
      Serial.println(F("EV_BEACON_FOUND"));
      break;
    case EV_BEACON_MISSED:
      Serial.println(F("EV_BEACON_MISSED"));
      break;
    case EV_BEACON_TRACKED:
      Serial.println(F("EV_BEACON_TRACKED"));
      break;
    case EV_JOINING:
      Serial.println(F("EV_JOINING"));
      break;
    case EV_JOINED:
      Serial.println(F("EV_JOINED"));
      {
        u4_t netid = 0;
        devaddr_t devaddr = 0;
        u1_t nwkKey[16];
        u1_t artKey[16];
        LMIC_getSessionKeys(&netid, &devaddr, nwkKey, artKey);
        Serial.print("netid: ");
        Serial.println(netid, DEC);
        Serial.print("devaddr: ");
        Serial.println(devaddr, HEX);
        Serial.print("AppSKey: ");
        for (size_t i = 0; i < sizeof(artKey); ++i) {
          if (i != 0)
            Serial.print("-");
          printHex2(artKey[i]);
        }
        Serial.println("");
        Serial.print("NwkSKey: ");
        for (size_t i = 0; i < sizeof(nwkKey); ++i) {
          if (i != 0)
            Serial.print("-");
          printHex2(nwkKey[i]);
        }
        Serial.println();
      }

      // Ignore the channels from the Join Accept
      forceTxSingleChannelDr();

      // Disable link check validation (automatically enabled
      // during join, but because slow data rates change max TX
      // size, we don't use it in this example.
      LMIC_setLinkCheckMode(0);
      break;
    /*
      || This event is defined but not used in the code. No
      || point in wasting codespace on it.
      ||
      || case EV_RFU1:
      ||     Serial.println(F("EV_RFU1"));
      ||     break;
    */
    case EV_JOIN_FAILED:
      Serial.println(F("EV_JOIN_FAILED"));
      break;
    case EV_REJOIN_FAILED:
      Serial.println(F("EV_REJOIN_FAILED"));
      break;
    case EV_TXCOMPLETE:
      Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
      if (LMIC.txrxFlags & TXRX_ACK)
        Serial.println(F("Received ack"));
      if (LMIC.dataLen) {
        Serial.print(F("Received "));
        Serial.print(LMIC.dataLen);
        Serial.println(F(" bytes of payload"));
      }
      // Schedule next transmission
      os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(TX_INTERVAL), do_send);
      break;
    case EV_LOST_TSYNC:
      Serial.println(F("EV_LOST_TSYNC"));
      break;
    case EV_RESET:
      Serial.println(F("EV_RESET"));
      break;
    case EV_RXCOMPLETE:
      // data received in ping slot
      Serial.println(F("EV_RXCOMPLETE"));
      break;
    case EV_LINK_DEAD:
      Serial.println(F("EV_LINK_DEAD"));
      break;
    case EV_LINK_ALIVE:
      Serial.println(F("EV_LINK_ALIVE"));
      break;
    /*
      || This event is defined but not used in the code. No
      || point in wasting codespace on it.
      ||
      || case EV_SCAN_FOUND:
      ||    Serial.println(F("EV_SCAN_FOUND"));
      ||    break;
    */
    case EV_TXSTART:
      Serial.println(F("EV_TXSTART"));
      break;
    case EV_TXCANCELED:
      Serial.println(F("EV_TXCANCELED"));
      break;
    case EV_RXSTART:
      /* do not print anything -- it wrecks timing */
      break;
    case EV_JOIN_TXCOMPLETE:
      Serial.println(F("EV_JOIN_TXCOMPLETE: no JoinAccept"));
      break;

    default:
      Serial.print(F("Unknown event: "));
      Serial.println((unsigned) ev);
      break;
  }
}

void do_send(osjob_t* j) {
  // Check if there is not a current TX/RX job running
  if (LMIC.opmode & OP_TXRXPEND) {
    Serial.println(F("OP_TXRXPEND, not sending"));
  } else {
    // Prepare upstream data transmission at the next possible time.
    LMIC_setTxData2(1, mydata, sizeof(mydata) - 1, 0);
    Serial.println(F("Packet queued"));
  }
  // Next TX is scheduled after TX_COMPLETE event.
}

void setup() {
  Serial.begin(74880);
  Serial.println(F("Starting"));

#ifdef VCC_ENABLE
  // For Pinoccio Scout boards
  pinMode(VCC_ENABLE, OUTPUT);
  digitalWrite(VCC_ENABLE, HIGH);
  delay(1000);
#endif

  //LMIC_setLinkCheckMode(0);   // Disable link check validation
  //LMIC_setAdrMode(false);     // Disable ADR
  //LMIC.dn2Dr = DR_SF9;        // TTN uses SF9 for its RX2 window.
  //LMIC_setDrTxpow(DR_SF7, 14); // Set data rate and transmit power for uplink (note: txpow seems to be ignored by the library)
  //LMIC_setClockError(MAX_CLOCK_ERROR * 10 / 100);

  // LMIC init
  os_init();
  // Reset the MAC state. Session and pending data transfers will be discarded.
  LMIC_reset();

  // Make LMiC initialize the default channels, choose a channel, and
  // schedule the OTAA join
  LMIC_startJoining();

  // LMiC will already have decided to send on one of the 3 default
  // channels; ensure it uses the one we want
  LMIC.txChnl = channel;

  // ...and make sure we see the EV_JOINING event being logged
  os_runloop_once();

  // Start job (sending automatically starts OTAA too)
  do_send(&sendjob);
}

void loop() {
  os_runloop_once();
}
