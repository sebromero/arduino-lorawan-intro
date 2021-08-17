#include <MKRWAN.h>
#include "arduino_secrets.h"

#define ANALOG_SENSOR_PIN A2

LoRaModem modem;
int analogSensorValue;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(ANALOG_SENSOR_PIN, INPUT); // Configures the analog pin as an input

  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };

  connectToLoRaWAN();
}

void connectToLoRaWAN(){
  Serial.println("Connecting...");
  int connected = modem.joinOTAA(APP_EUI, APP_KEY);

  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }

  delay(5000);
}

void sendSensorValue(){
  Serial.println("Sending message...");
  modem.setPort(3);
  modem.beginPacket();
  // Sends 4 bytes of data. Use the integer payload decoder on TTS
  modem.write<int>(analogSensorValue);
    
  int error = modem.endPacket(true);
  
  if (error > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
  }
  
  Serial.println();
}

void loop() {
  analogSensorValue = analogRead(ANALOG_SENSOR_PIN);

  Serial.print("Sensor value = ");
  Serial.println(analogSensorValue);
  Serial.println(); // print an empty line

  sendSensorValue();  
  delay(120000); // wait 120 seconds to print again
}
