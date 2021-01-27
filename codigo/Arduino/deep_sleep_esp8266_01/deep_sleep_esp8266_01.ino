/* Como poner el ESP8266 en modo deep-sleep
 */

void setup(){
   Serial.begin(74880);
   Serial.setTimeout(2000);

   Serial.println("Estoy despierto");
   Serial.print("Voy a dormir unos segundos");

   ESP.deepSleep(10e6);
}

void loop(){}
