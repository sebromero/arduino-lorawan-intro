#include <MKRWAN.h>
#include <Arduino_MKRENV.h>
#include "arduino_secrets.h"

LoRaModem modem;

void setup() {  
  Serial.begin(115200);
  while (!Serial);

  ENV.begin();
  pinMode(LED_BUILTIN, OUTPUT);  
  
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  
  if (modem.version() != ARDUINO_FW_VERSION) {
    Serial.println("Please make sure that the latest modem firmware is installed.");
    Serial.println("To update the firmware upload the 'MKRWANFWUpdate_standalone.ino' sketch.");
  }
  
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());

  Serial.println("Connecting...");
  int connected = modem.joinOTAA(APP_EUI, APP_KEY);

  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }
    
  modem.minPollInterval(60); // Default is 300s
  Serial.println("Waiting for messages...");
}

void loop() {
  delay(60 * 1000); // Wait 60 secs before polling again
  
  modem.poll();
  delay(5000);

  if (!modem.available()) {
    Serial.println("No downlink message received at this time.");    
    return;
  }

  char dataBuffer[64];
  int i = 0;
  while (modem.available()) {
    dataBuffer[i++] = (char)modem.read();
  }

  Serial.print("Received: ");
  for (unsigned int j = 0; j < i; j++) {
    Serial.print(dataBuffer[j] >> 4, HEX);
    Serial.print(dataBuffer[j] & 0xF, HEX);
    Serial.print(" ");
  }
  Serial.println();

  if(dataBuffer[0] == 1){
    digitalWrite(LED_BUILTIN, HIGH);
  } else if(dataBuffer[0] == 0) {
    digitalWrite(LED_BUILTIN, LOW);
  }
  
}
