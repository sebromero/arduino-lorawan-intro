#include <MKRWAN.h>

LoRaModem modem;

void setup() {  
  Serial.begin(115200);
  while (!Serial);
   
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());
}

void loop() {}
