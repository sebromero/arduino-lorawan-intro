#include <MKRWAN.h>
#include "arduino_secrets.h"

LoRaModem modem;

// Enter your sensitive data in the secret tab or arduino_secrets.h
String appEui = APP_EUI;
String appKey = APP_KEY;

void setup() {
  // Initialize serial port at 9600 bauds
  Serial.begin(9600);
  while (!Serial);
  
  // Initialize LoRa module with the US915-928 region parameters
  if (!modem.begin(US915)) {
    Serial.println("Failed to start module");
    while (1) {}
  };

  // Device module version and EUI
  delay(5000);
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());

  // Enable US915-928 channels
  // LoRaWAN® Regional Parameters and TTN specification: channels 8 to 15 plus 65 
  modem.sendMask("ff000001f000ffff00020000");
  Serial.println(modem.getChannelMask());
  modem.setADR(true);
  join();
}

void join() {
  // Try to connect
  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong, retrying...");
    join();
  }
}

void loop(){}
